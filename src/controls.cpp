// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}



// Initial position : on +Z
glm::vec3 position = glm::vec3( 0, 0, -36); 
// Initial horizontal angle : toward -Z
float horizontalAngle = 0;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 30.0f;

float speed = 5.0f; // 3 units / second
float mouseSpeed = 2.f;

float fovSpeed = 30.f;


glm::vec3 getPosition()
{
	return position;
}

void computeMatricesFromInputs(GLFWwindow *window, int width, int height, float dt)
{
	// glfwGetTime is called only once, the first time this function is called
	//static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	//double currentTime = glfwGetTime();
	float deltaTime = dt;//float(currentTime - lastTime);

	// Get mouse position
	//double xpos, ypos;
	//glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse position for next frame
    //glfwSetCursorPos(window, width/2, height/2);

	// Move forward
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		verticalAngle += mouseSpeed * dt;
	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		verticalAngle -= mouseSpeed * dt;
	}
	// Move forward
	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		horizontalAngle += mouseSpeed * dt;
	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		horizontalAngle -= mouseSpeed * dt;
	}
	// Move forward
	if (glfwGetKey( window, GLFW_KEY_KP_ADD ) == GLFW_PRESS){
		initialFoV += fovSpeed * dt;
	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_KP_SUBTRACT ) == GLFW_PRESS){
		initialFoV -= fovSpeed * dt;
	}

	// Compute new orientation
	//horizontalAngle += mouseSpeed * float(width/2 - xpos );
	//verticalAngle   += mouseSpeed * float(height/2 - ypos );

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
	
	glm::vec3 front = glm::vec3(
		sin(horizontalAngle), 
		0,
		cos(horizontalAngle)
	);

	// Up vector
	glm::vec3 up = glm::cross( right, direction );

	glm::vec3 upp(0, 1, 0);

	// Move forward
	if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS){
		position += front * dt * speed;
	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS){
		position -= front * dt * speed;
	}
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS){
		position += right * dt * speed;
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS){
		position -= right * dt * speed;
	}
	// Go up
	if (glfwGetKey( window, GLFW_KEY_SPACE ) == GLFW_PRESS){
		position += upp * dt * speed;
	}
	// Go down
	if (glfwGetKey( window, GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS){
		position -= upp * dt * speed;
	}

	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.
	float aspectRatio = (float)(width) / (float)(height);
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(FoV), aspectRatio, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix       = glm::lookAt(
								position,           // Camera is here
								position+direction, // and looks here : at the same position, plus "direction"
								up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );

	// For the next frame, the "last time" will be "now"
	//lastTime = currentTime;
}