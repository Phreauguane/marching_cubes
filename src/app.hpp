#include "glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/transform.hpp>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "controls.hpp"
#include "marchingCubes.h"

/* define mysnprintf to be either snprintf (POSIX) or sprintf_s (MS Windows) */
#ifdef WIN32
#define mysnprintf sprintf_s
#else
#define mysnprintf snprintf
#endif

#define APP_TITLE "Marching Cubes"

/* OpenGL debug output error level */
typedef enum {
	DEBUG_OUTPUT_DISABLED=0,
	DEBUG_OUTPUT_ERRORS_ONLY,
	DEBUG_OUTPUT_ALL
} DebugOutputLevel;

/* AppConfig: application configuration, controllable via command line arguments*/
struct AppConfig {
	int posx;
	int posy;
	int width;
	int height;
	bool decorated;
	bool fullscreen;
	unsigned int frameCount;
	DebugOutputLevel debugOutputLevel;
	bool debugOutputSynchronous;

	AppConfig() :
		posx(100),
		posy(100),
		width(1280),
		height(720),
		decorated(true),
		fullscreen(false),
		frameCount(0),
		debugOutputLevel(DEBUG_OUTPUT_DISABLED),
		debugOutputSynchronous(false)
	{}
};

class Mesh {
public:
	glm::vec3 pos;
	GLuint vbo[2];		/* vertex and index buffer names */
	GLuint vao;		/* vertex array object */
	GLuint iCount;
	bool loaded;
	glm::mat4 model;	/* local model transformation */
};

/* App: We encapsulate all of our application state in this struct.
 * We use a single instance of this object (in main), and set a pointer to
 * this as the user-defined pointer for GLFW windows. That way, we have access
 * to this data structure without ever using global variables.
 */
typedef struct {
	/* the window and related state */
	GLFWwindow *win;
	int width, height;
	unsigned int flags;

	/* timing */
	double timeCur, timeDelta;
	double avg_frametime;
	double avg_fps;
	unsigned int frame;

	/* keyboard handling */
	bool pressedKeys[GLFW_KEY_LAST+1];
	bool releasedKeys[GLFW_KEY_LAST+1];

	/* the mesh we want to render */
	std::vector<Mesh> mesh;

	/* the OpenGL state we need for the shaders */
	GLuint program;		/* shader program */
	GLint locProjection;
	GLint locModelView;
	GLint locTime;

	/*  the gloabal transformation matrices */
	glm::mat4 projection;
	glm::mat4 view;
} App;

/****************************************************************************
 * UTILITY FUNCTIONS: warning output, gl error checking                     *
 ****************************************************************************/

/* Print a info message to stdout, use printf syntax. */
static void info (const char *format, ...)
{
	va_list args;
	va_start(args, format);
	vfprintf(stdout,format, args);
	va_end(args);
	fputc('\n', stdout);
}

/* Print a warning message to stderr, use printf syntax. */
static void warn (const char *format, ...)
{
	va_list args;
	va_start(args, format);
	vfprintf(stderr,format, args);
	va_end(args);
	fputc('\n', stderr);
}

/* Check for GL errors. If ignore is not set, print a warning if an error was
 * encountered.
 * Returns GL_NO_ERROR if no errors were set. */
static GLenum getGLError(const char *action, bool ignore=false, const char *file=NULL, const int line=0)
{
	GLenum e,err=GL_NO_ERROR;

	do {
		e=glGetError();
		if ( (e != GL_NO_ERROR) && (!ignore) ) {
			err=e;
			if (file)
				fprintf(stderr,"%s:",file);
			if (line)
				fprintf(stderr,"%d:",line);
			warn("GL error 0x%x at %s",(unsigned)err,action);
		}
	} while (e != GL_NO_ERROR);
	return err;
}

/* helper macros:
 * define GL_ERROR_DBG() to be present only in DEBUG builds. This way, you can
 * add error checks at strategic places without influencing the performance
 * of the RELEASE build */
#ifdef NDEBUG
#define GL_ERROR_DBG(action) (void)0
#else
#define GL_ERROR_DBG(action) getGLError(action, false, __FILE__, __LINE__)
#endif


/****************************************************************************
 * GL DEBUG MESSAGES                                                        *
 ****************************************************************************/

/* Newer versions of the GL support the generation of human-readable messages
   for GL errors, performance warnings and hints. These messages are
   forwarded to a debug callback which has to be registered with the GL
   context. Debug output may only be available in special debug context... */

/* translate the debug message "source" enum to human-readable string */
static const char *
translateDebugSourceEnum(GLenum source)
{
	const char *s;

	switch (source) {
		case GL_DEBUG_SOURCE_API:
			s="API";
			break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			s="window system";
			break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			s="shader compiler";
			break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:
			s="3rd party";
			break;
		case GL_DEBUG_SOURCE_APPLICATION:
			s="application";
			break;
		case GL_DEBUG_SOURCE_OTHER:
			s="other";
			break;
		default:
			s="[UNKNOWN SOURCE]";
	}

	return s;
}

/* translate the debug message "type" enum to human-readable string */
static const char *
translateDebugTypeEnum(GLenum type)
{
	const char *s;

	switch (type) {
		case GL_DEBUG_TYPE_ERROR:
			s="error";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			s="deprecated";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			s="undefined behavior";
			break;
		case GL_DEBUG_TYPE_PORTABILITY:
			s="portability";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			s="performance";
			break;
		case GL_DEBUG_TYPE_OTHER:
			s="other";
			break;
		default:
			s="[UNKNOWN TYPE]";
	}
	return s;
}

/* translate the debug message "xeverity" enum to human-readable string */
static const char *
translateDebugSeverityEnum(GLenum severity)
{
	const char *s;

	switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:
			s="high";
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			s="medium";
			break;
		case GL_DEBUG_SEVERITY_LOW:
			s="low";
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			s="notification";
			break;
		default:
			s="[UNKNOWN SEVERITY]";
	}

	return s;
}

/* debug callback of the GL */
extern void APIENTRY
debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
			  GLsizei length, const GLchar *message, const GLvoid* userParam)
{
	/* we pass a pointer to our application config to the callback as userParam */
	const AppConfig *cfg=(const AppConfig*)userParam;

	switch(type) {
		case GL_DEBUG_TYPE_ERROR:
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			if (cfg->debugOutputLevel >= DEBUG_OUTPUT_ERRORS_ONLY) {
				warn("GLDEBUG: %s %s %s [0x%x]: %s",
					translateDebugSourceEnum(source),
					translateDebugTypeEnum(type),
					translateDebugSeverityEnum(severity),
					id, message);
			}
			break;
		default:
			if (cfg->debugOutputLevel >= DEBUG_OUTPUT_ALL) {
				warn("GLDEBUG: %s %s %s [0x%x]: %s",
					translateDebugSourceEnum(source),
					translateDebugTypeEnum(type),
					translateDebugSeverityEnum(severity),
					id, message);
			}
	}
}

/****************************************************************************
 * UTILITY FUNCTIONS: print information about the GL context                *
 ****************************************************************************/

/* Print info about the OpenGL context */
static void printGLInfo()
{
	/* get infos about the GL implementation */
	info("OpenGL: %s %s %s",
			glGetString(GL_VENDOR),
			glGetString(GL_RENDERER),
			glGetString(GL_VERSION));
	info("OpenGL Shading language: %s",
			glGetString(GL_SHADING_LANGUAGE_VERSION));
}

/* List all supported GL extensions */
static void listGLExtensions()
{
	GLint num=0;
	GLuint i;
	glGetIntegerv(GL_NUM_EXTENSIONS, &num);
	info("GL extensions supported: %d", num);
	if (num < 1) {
		return;
	}

	for (i=0; i<(GLuint)num; i++) {
		const GLubyte *ext=glGetStringi(GL_EXTENSIONS,i);
		if (ext) {
			info("  %s",ext);
		}
	}
}

/****************************************************************************
 * SETTING UP THE GL STATE                                                  *
 ****************************************************************************/

/* Initialize the global OpenGL state. This is called once after the context
 * is created. */
static void initGLState(const AppConfig&cfg)
{
	printGLInfo();
	listGLExtensions();

	if (cfg.debugOutputLevel > DEBUG_OUTPUT_DISABLED) {
		if (GLAD_GL_VERSION_4_6) {
			info("enabling GL debug output [via OpenGL >= 4.6]");
			glDebugMessageCallback(debugCallback,&cfg);
			glEnable(GL_DEBUG_OUTPUT);
			if (cfg.debugOutputSynchronous) {
				glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			} else {
				glDisable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			}
		} else {
			warn("GL debug output requested, but not supported by the context");
		}
	}

	/* we set these once and never change them, so there is no need
	 * to set them during the main loop */
	glEnable(GL_DEPTH_TEST);

	/* We do not enable backface culling, since the "cut" shader works
	 * best when one can see through the cut-out front faces... */
	//glEnable(GL_CULL_FACE);
}

/****************************************************************************
 * SHADER COMPILATION AND LINKING                                           *
 ****************************************************************************/

/* Print the info log of the shader compiler/linker.
 * If program is true, obj is assumed to be a program object, otherwise, it
 * is assumed to be a shader object.
 */
static void printInfoLog(GLuint obj, bool program)
{
	char log[16384];
	if (program) {
		glGetProgramInfoLog(obj, sizeof(log), 0, log);
	} else {
		glGetShaderInfoLog(obj, sizeof(log), 0, log);
	}
	/* technically, this is not strictly necessary as the GL implementation
	 * is required to properly terminate the string, but we never trust
	 * other code and make sure the string is terminated before running out
	 * of the buffer. */
	log[sizeof(log)-1]=0;
	fprintf(stderr,"%s\n",log);
}

/* Create a new shader object, attach "source" as source string,
 * and compile it.
 * Returns the name of the newly created shader object, or 0 in case of an
 * error.
 */
static  GLuint shaderCreateAndCompile(GLenum type, const GLchar *source)
{
	GLuint shader=0;
	GLint status;

	shader=glCreateShader(type);
	info("created shader object %u",shader);
	glShaderSource(shader, 1, (const GLchar**)&source, NULL);
	info("compiling shader object %u",shader);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		warn("Failed to compile shader");
		printInfoLog(shader,false);
		glDeleteShader(shader);
		shader=0;
	}

	return shader;
}

/* Create a new shader object by loading a file, and compile it.
 * Returns the name of the newly created shader object, or 0 in case of an
 * error.
 */
static  GLuint shaderCreateFromFileAndCompile(GLenum type, const char *filename)
{

	info("loading shader file '%s'",filename);
	FILE *file = fopen(filename, "rt");
	if(!file) {
		warn("Failed to open shader file '%s'", filename);
		return 0;
	}
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	GLchar *source = (GLchar*)malloc(size+1);
	if (!source) {
		warn("Failed to allocate memory for shader file '%s'", filename);
		fclose(file);
		return 0;
	}
	fseek(file, 0, SEEK_SET);
	source[fread(source, 1, size, file)] = 0;
	fclose(file);

	GLuint shader=shaderCreateAndCompile(type, source);
	free(source);
	return shader;
}

/* Create a program by linking a vertex and fragment shader object. The shader
 * objects should already be compiled.
 * Returns the name of the newly created program object, or 0 in case of an
 * error.
 */
static GLuint programCreate(GLuint vertex_shader, GLuint fragment_shader)
{
	GLuint program=0;
	GLint status;

	program=glCreateProgram();
	info("created program %u",program);

	if (vertex_shader)
		glAttachShader(program, vertex_shader);
	if (fragment_shader)
		glAttachShader(program, fragment_shader);

	/* hard-code the attribute indices for the attributeds we use */
	glBindAttribLocation(program, 0, "pos");
	glBindAttribLocation(program, 1, "nrm");
	glBindAttribLocation(program, 2, "clr");
	glBindAttribLocation(program, 3, "tex");

	/* hard-code the color number of the fragment shader output */
	glBindFragDataLocation(program, 0, "color");

	/* finally link the program */
	info("linking program %u",program);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		warn("Failed to link program!");
		printInfoLog(program,true);
		glDeleteProgram(program);
		return 0;
	}
	return program;
}

/* Create a program object directly from vertex and fragment shader source
 * files.
 * Returns the name of the newly created program object, or 0 in case of an
 * error.
 */
static GLenum programCreateFromFiles(const char *vs, const char *fs)
{
	GLuint id_vs=shaderCreateFromFileAndCompile(GL_VERTEX_SHADER, vs);
	GLuint id_fs=shaderCreateFromFileAndCompile(GL_FRAGMENT_SHADER, fs);
	GLuint program=programCreate(id_vs,id_fs);
	/* Delete the shader objects. Since they are still in use in the
	 * program object, OpenGL will not destroy them internally until
	 * the program object is destroyed. The caller of this function
	 * does not need to care about the shader objects at all. */
	info("destroying shader object %u",id_vs);
	glDeleteShader(id_vs);
	info("destroying shader object %u",id_fs);
	glDeleteShader(id_fs);
	return program;
}

/****************************************************************************
 * THE SHADERS WE USE                                                       *
 ****************************************************************************/

/* In this example, we load the shaders from file, and are able to re-load
 * them on keypress. */

/* Destroy all GL objects related to the shaders. */
void destroyShaders(App *app)
{
	if (app->program) {
		info("deleting program %u",app->program);
		glDeleteProgram(app->program);
		app->program=0;
	}
}

/* Create and compile the shaders and link them to a program and qeury
 * the locations of the uniforms we use.
 * Returns true if successfull and false in case of an error. */
bool initShaders(App *app, const char *vs, const char *fs)
{
	destroyShaders(app);
	app->program=programCreateFromFiles(vs, fs);
	if (app->program == 0)
		return false;

	app->locProjection=glGetUniformLocation(app->program, "projection");
	app->locModelView=glGetUniformLocation(app->program, "modelView");
	app->locTime=glGetUniformLocation(app->program, "time");
	info("program %u: location for \"projection\" uniform: %d",app->program, app->locProjection);
	info("program %u: location for \"modelView\" uniform: %d",app->program, app->locModelView);
	info("program %u: location for \"time\" uniform: %d",app->program, app->locTime);

	return true;
}

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

void initMesh(Mesh *mesh, std::vector<Vertex> vertices, std::vector<GLushort> indices)
{
	mesh->iCount = indices.size();
	/* set up VAO and vertex and element array buffers */
	glGenVertexArrays(1,&mesh->vao);
	glBindVertexArray(mesh->vao);
	info("Mesh: created VAO %u", mesh->vao);

	glGenBuffers(2,mesh->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);
	info("Mesh: created VBO %u for %u bytes of vertex data", mesh->vbo[0], (unsigned)(sizeof(Vertex) * vertices.size()));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->vbo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indices.size(), &indices[0], GL_DYNAMIC_DRAW);
	info("Mesh: created VBO %u for %u bytes of element data", mesh->vbo[1], (unsigned)(sizeof(GLushort) * indices.size()));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(offsetof(Vertex,pos)));
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), BUFFER_OFFSET(offsetof(Vertex,clr)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	mesh->model = glm::mat4(1.0f);
	GL_ERROR_DBG("mesh initialization");
	mesh->loaded = true;
}

void destroyMesh(Mesh *mesh)
{
	glBindVertexArray(0);
	if (mesh->vao) {
		info("Mesh: deleting VAO %u", mesh->vao);
		glDeleteVertexArrays(1,&mesh->vao);
		mesh->vao=0;
	}
	if (mesh->vbo[0] || mesh->vbo[1]) {
		info("Mesh: deleting VBOs %u %u", mesh->vbo[0], mesh->vbo[1]);
		glDeleteBuffers(2,mesh->vbo);
		mesh->vbo[0]=0;
		mesh->vbo[1]=0;
	}
	mesh->loaded = false;
}

/* flags */
#define APP_HAVE_GLFW	0x1	/* we have called glfwInit() and should terminate it */
#define APP_HAVE_GL		0x2	/* we have a valid GL context */

/****************************************************************************
 * WINDOW-RELATED CALLBACKS                                                 *
 ****************************************************************************/

/* This function is registered as the framebuffer size callback for GLFW,
 * so GLFW will call this whenever the window is resized. */
static void callback_Resize(GLFWwindow *win, int w, int h)
{
	App *app=(App*)glfwGetWindowUserPointer(win);
	info("new framebuffer size: %dx%d pixels",w,h);

	/* store curent size for later use in the main loop */
	app->width=w;
	app->height=h;

	/* we _could_ directly set the viewport here ... */
}

/* This function is registered as the keayboard callback for GLFW, so GLFW
 * will call this whenever a key is pressed. */
static void callback_Keyboard(GLFWwindow *win, int key, int scancode, int action, int mods)
{
	/* The shaders we load on the number keys. We always load a combination of
	 * a vertex and a fragment shader. */
	static const char* shaders[][2]={
		/* 0 */ {"../shaders/minimal.vs.glsl",      "../shaders/minimal.fs.glsl"     },
		/* 1 */ {"../shaders/color.vs.glsl",        "../shaders/color.fs.glsl"       },
		/* 2 */ {"../shaders/cut.vs.glsl",          "../shaders/cut.fs.glsl"         },
		/* 3 */ {"../shaders/wobble.vs.glsl",       "../shaders/color.fs.glsl"       },
		/* 4 */ {"../shaders/experimental.vs.glsl", "../shaders/experimental.fs.glsl"},
		/* placeholders for additional shaders */
		/* 5 */ {"../shaders/yourshader.vs.glsl", "../shaders/yourshader.fs.glsl"},
		/* 6 */ {"../shaders/yourshader.vs.glsl", "../shaders/yourshader.fs.glsl"},
		/* 7 */ {"../shaders/yourshader.vs.glsl", "../shaders/yourshader.fs.glsl"},
		/* 8 */ {"../shaders/yourshader.vs.glsl", "../shaders/yourshader.fs.glsl"},
		/* 9 */ {"../shaders/yourshader.vs.glsl", "../shaders/yourshader.fs.glsl"}
	};

	App *app=(App*)glfwGetWindowUserPointer(win);

	if (key < 0 || key > GLFW_KEY_LAST) {
		warn("invalid key code %d?!",key);
		return;
	}

	if (action == GLFW_RELEASE) {
		app->pressedKeys[key] = false;
	} else {
		if (!app->pressedKeys[key]) {
			/* handle certain keys */
			if (key >= '0' && key <= '9') {
				initShaders(app, shaders[key - '0'][0], shaders[key - '0'][1]);
			} else {
				switch (key) {
					case GLFW_KEY_ESCAPE:
						glfwSetWindowShouldClose(win,1);
						break;
				}
			}
		}
		app->pressedKeys[key] = true;
	}
}
