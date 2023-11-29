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
#include "app.hpp"

/****************************************************************************
 * GLOBAL INITIALIZATION AND CLEANUP                                        *
 ****************************************************************************/

/* Initialize the Cube Application.
 * This will initialize the app object, create a windows and OpenGL context
 * (via GLFW), initialize the GL function pointers via GLEW and initialize
 * the cube.
 * Returns true if successfull or false if an error occured. */
bool initApplication(App *app, const AppConfig& cfg)
{
	int i;
	int w, h, x, y;
	bool debugCtx=(cfg.debugOutputLevel > DEBUG_OUTPUT_DISABLED);

	/* Initialize the app structure */
	app->win=NULL;
	app->flags=0;
	app->avg_frametime=-1.0;
	app->avg_fps=-1.0;
	app->frame = 0;

	for (i=0; i<=GLFW_KEY_LAST; i++)
		app->pressedKeys[i]=app->releasedKeys[i]=false;

	for (Mesh m: app->mesh)
	{
		m.vbo[0]=m.vbo[1]=m.vao=0;
	}
	app->program=0;

	/* initialize GLFW library */
	info("initializing GLFW");
	if (!glfwInit()) {
		warn("Failed to initialze GLFW");
		return false;
	}

	app->flags |= APP_HAVE_GLFW;

	/* request a OpenGL 3.2 core profile context */
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, (debugCtx)?GL_TRUE:GL_FALSE);

	GLFWmonitor *monitor = NULL;
	x = cfg.posx;
	y = cfg.posy;
	w = cfg.width;
	h = cfg.height;

	if (cfg.fullscreen) {
		monitor = glfwGetPrimaryMonitor();
	}
	if (monitor) {
		glfwGetMonitorPos(monitor, &x, &y);
		const GLFWvidmode *v = glfwGetVideoMode(monitor);
		if (v) {
			w = v->width;
			h = v->height;
			info("Primary monitor: %dx%d @(%d,%d)", w, h, x, y);
		}
		else {
			warn("Failed to query current video mode!");
		}
	}

	if (!cfg.decorated) {
		glfwWindowHint(GLFW_DECORATED, GL_FALSE);
	}

	/* create the window and the gl context */
	info("creating window and OpenGL context");
	app->win=glfwCreateWindow(w, h, APP_TITLE, monitor, NULL);
	if (!app->win) {
		warn("failed to get window with OpenGL 3.2 core context");
		return false;
	}

	app->width = w;
	app->height = h;

	if (!monitor) {
		glfwSetWindowPos(app->win, x, y);
	}

	/* store a pointer to our application context in GLFW's window data.
	 * This allows us to access our data from within the callbacks */
	glfwSetWindowUserPointer(app->win, app);
	/* register our callbacks */
	glfwSetFramebufferSizeCallback(app->win, callback_Resize);
	glfwSetKeyCallback(app->win, callback_Keyboard);

	/* make the context the current context (of the current thread) */
	glfwMakeContextCurrent(app->win);

	/* ask the driver to enable synchronizing the buffer swaps to the
	 * VBLANK of the display. Depending on the driver and the user's
	 * setting, this may have no effect. But we can try... */
	glfwSwapInterval(1);

	/* initialize glad,
	 * this will load all OpenGL function pointers
	 */
	info("initializing glad");
	if (!gladLoadGL()) {
		warn("failed to intialize glad GL extension loader");
		return false;
	}

	if (!GLAD_GL_VERSION_3_2) {
		warn("failed to load at least GL 3.2 functions via GLAD");
		return false;
	}

	app->flags |= APP_HAVE_GL;

	/* generate meshes */
	//std::vector<Vertex> verts;
	//std::vector<GLushort> inds;

	/*----------------------------------*/

	//glm::vec3 start = glm::vec3(0);
	//glm::vec3 end   = glm::vec3(8, 256, 8);
	//genMarchingCubes(0.25f, verts, inds, start, end, noiseIsoSurf);
	//Mesh m;
	//initMesh(&m, verts, inds);
	//app->mesh.push_back(m);

	//int chunks = 8;
//
	//for (int X = 0; X < chunks; X++)
	//{
	//	for (int Y = 0; Y < chunks; Y++)
	//	{
	//		for (int Z = 0; Z < chunks; Z++)
	//		{
	//			glm::vec3 start = glm::vec3(X, Y, Z) * 16.f;
	//			glm::vec3 end = glm::vec3(X + 1, Y + 1, Z + 1) * 16.f;
	//			genMarchingCubes(0.45f, verts, inds, start, end, noiseIsoSurf);
	//			//genMarchingCubes(chunk, glm::vec3(X, Y, Z) * 16.f, verts, inds);
	//			Mesh m;
	//			initMesh(&m, verts, inds);
	//			app->mesh.push_back(m);
	//		}
	//	}
	//}
	


	//genSphereVertices(verts, inds);
	//Mesh m2;
	//initMesh(&m2, verts, inds);
	//app->mesh.push_back(m2);

	//genFloor(20.f, 30.f, -10.f, verts, inds);
	//Mesh m3;
	//initMesh(&m3, verts, inds);
	//app->mesh.push_back(m3);

	/* initialize the GL context */
	initGLState(cfg);
	if (!initShaders(app,"../shaders/color.vs.glsl","../shaders/color.fs.glsl")) {
		warn("something wrong with our shaders...");
		return false;
	}

	/* initialize the timer */
	app->timeCur=glfwGetTime();

	return true;
}

/* Clean up: destroy everything the cube app still holds */
static void destroyApp(App *app)
{
	if (app->flags & APP_HAVE_GLFW) {
		if (app->win) {
			if (app->flags & APP_HAVE_GL) {
				for (int i = 0; i < app->mesh.size(); i++) destroyMesh(&(app->mesh[i]));
				destroyShaders(app);
			}
			glfwDestroyWindow(app->win);
		}
		glfwTerminate();
	}
}

/****************************************************************************
 * DRAWING FUNCTION                                                         *
 ****************************************************************************/

/* This draws the complete scene for a single eye */
static void
drawScene(App *app)
{
	for (Mesh m: app->mesh)
	{
		if (m.loaded)
		{
		/* combine model and view matrices to the modelView matrix our
		 * shader expects */
		glm::mat4 modelView = app->view * m.model;

		/* use the program and update the uniforms */
		glUseProgram(app->program);
		glUniformMatrix4fv(app->locProjection, 1, GL_FALSE, glm::value_ptr(app->projection));
		glUniformMatrix4fv(app->locModelView, 1, GL_FALSE, glm::value_ptr(modelView));
		glUniform1f(app->locTime, (GLfloat)app->timeCur);

		/* draw the cube */
		glBindVertexArray(m.vao);
		glDrawElements(GL_TRIANGLES, m.iCount, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));

		/* "unbind" the VAO and the program. We do not have to do this.
		* OpenGL is a state machine. The last binings will stay effective
		* until we actively change them by binding something else. */
		glBindVertexArray(0);
		}
	}
}

/* Set up projection and view matrices
 * Although this is constant in this example, we re-calculate it per frame.
 * For a moving camera, the view matrix would typically change per frame.
 */
static void
setProjectionAndView(App *app)
{
	app->projection = getProjectionMatrix();
	app->view = getViewMatrix();
}

/* The main drawing function. This is responsible for drawing the next frame,
 * it is called in a loop as long as the application runs */
static void
displayFunc(App *app, const AppConfig& cfg, float dt)
{
	/* rotate the cube */
	//app->mesh.model = glm::rotate(app->mesh.model, (float)(glm::half_pi<double>() * app->timeDelta), glm::vec3(0.8f, 0.6f, 0.1f));

	/* set the viewport (might have changed since last iteration) */
	glViewport(0, 0, app->width, app->height);

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); /* clear the buffers */

	computeMatricesFromInputs(app->win, app->width, app->height, dt);
	setProjectionAndView(app);
	drawScene(app);

	/* finished with drawing, swap FRONT and BACK buffers to show what we
	 * have rendered */
	glfwSwapBuffers(app->win);

	/* In DEBUG builds, we also check for GL errors in the display
	 * function, to make sure no GL error goes unnoticed. */
	GL_ERROR_DBG("display function");
}

/****************************************************************************
 * MAIN LOOP                                                                *
 ****************************************************************************/

/* The main loop of the application. This will call the display function
 *  until the application is closed. This function also keeps timing
 *  statistics. */
static void mainLoop(App *app, const AppConfig& cfg)
{
	unsigned int frame=0;
	double start_time=glfwGetTime();
	double last_time=start_time;

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glCullFace(GL_FRONT);

	info("entering main loop");
	while (!glfwWindowShouldClose(app->win)) {
		/* update the current time and time delta to last frame */
		double now=glfwGetTime();
		app->timeDelta = now - app->timeCur;
		app->timeCur = now;

		glm::vec3 pos = getPosition();

		/* update FPS estimate at most once every second */
		double elapsed = app->timeCur - last_time;
		if (elapsed >= 1.0) {
			char WinTitle[80];
			app->avg_frametime=1000.0 * elapsed/(double)frame;
			app->avg_fps=(double)frame/elapsed;
			last_time=app->timeCur;
			frame=0;
			/* update window title */
			mysnprintf(WinTitle, sizeof(WinTitle), APP_TITLE "   /// AVG: %4.2fms/frame (%.1ffps)", app->avg_frametime, app->avg_fps);
			glfwSetWindowTitle(app->win, WinTitle);
			info("frame time: %4.2fms/frame (%.1ffps)",app->avg_frametime, app->avg_fps);
		}

		/*
			Chunks : 16x16x16 cubes
			Render Distance : 3 chunks (in each direction)
		*/
		int RenderDist = 5;
		
		std::vector<glm::vec3> toLoad;
		std::vector<unsigned int> toUnloadInds;

		if (glfwGetKey( app->win, GLFW_KEY_0 ) == GLFW_PRESS)
		{
			app->mesh.clear();
		}

		// ----------------------------------------
		// --- replace old chunks with new ones ---
		// ----------------------------------------
		//
		//else if (app->loadedChunks[i] == currentChunk)
		//{
		//	app->loadedChunks.erase(std::next(app->loadedChunks.begin(), i));
		//	destroyMesh(&(app->mesh[i]));
		//
		//}
		// detect wich chunks need to be unloaded
		for (unsigned int i = 0; i < app->mesh.size(); i++)
		{
			float d = dist(pos, (app->mesh[i].pos * 16.f) + glm::vec3(8.f));
			if (d > RenderDist * 16.f)
				{
					toUnloadInds.push_back(i);
				}
		}

		for (int X = -RenderDist; X < RenderDist; X++)
		{
			for (int Y = -RenderDist; Y < RenderDist; Y++)
			{
				for (int Z = -RenderDist; Z < RenderDist; Z++)
				{
					glm::vec3 intPos = glm::vec3(int(pos.x) / 16, int(pos.y) / 16, int(pos.z) / 16);
					glm::vec3 currentChunk = intPos + glm::vec3(X, Y, Z);
					float d = dist(pos, (currentChunk * 16.f) + glm::vec3(8.f));
					if (d <= RenderDist * 16.f)
					{
					bool toLoad = true;
					for (int i = 0; i < app->mesh.size(); i++)
					{
						if (app->mesh[i].pos == currentChunk && toLoad)
						{
							toLoad = false;
							break;
						}
					}
					if (toLoad)
					{
						glm::vec3 start = currentChunk * 16.f;
						glm::vec3 end = start + glm::vec3(16.f);
						std::vector<Vertex> verts;
						std::vector<GLushort> inds;
						genMarchingCubes(0.75f, verts, inds, start, end, defIsoSurf);
						unsigned int i = app->mesh.size();
						if (toUnloadInds.size() > 0)
						{
							i = toUnloadInds[toUnloadInds.size() - 1];
							toUnloadInds.pop_back();
							destroyMesh(&(app->mesh[i]));
						}
						else
							app->mesh.push_back(*(new Mesh));
						initMesh(&(app->mesh[i]), verts, inds);
						app->mesh[i].pos = currentChunk;
					}}
				}
			}
		}
		
		for (int i = 0; i < toUnloadInds.size(); i++)
		{
			destroyMesh(&(app->mesh[toUnloadInds[i]]));
		}

		/* call the display function */
		displayFunc(app, cfg, app->timeDelta);
		app->frame++;
		frame++;
		if (cfg.frameCount && app->frame >= cfg.frameCount) {
			break;
		}
		/* This is needed for GLFW event handling. This function
		 * will call the registered callback functions to forward
		 * the events to us. */
		glfwPollEvents();
	}
	info("left main loop\n%u frames rendered in %.1fs seconds == %.1ffps",
		app->frame,(app->timeCur-start_time),
		(double)app->frame/(app->timeCur-start_time) );
}