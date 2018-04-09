#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer.h"
#include "camera.h"
#include "sprite.h"
#include "gameobject.h"
#include "Scene00.h"

double _deltaTime;

void processInput(GLFWwindow *window);
double CalculateDeltaTime();

int main() {
	Renderer renderer; // Create renderer

	_deltaTime = 0;

	Scene00* scene00 = new Scene00();

	while (!glfwWindowShouldClose(renderer.Window())) {
		processInput(renderer.Window()); // Input

		CalculateDeltaTime();

		scene00->GetCamera()->UpdateCamera(); // Update camera

		// Update and render scene
		scene00->UpdateScene(_deltaTime);
		renderer.RenderScene(scene00);

		// glfw: poll IO events
		glfwPollEvents();
	}
	return 0;
}

double CalculateDeltaTime() {
	static double lastTime = glfwGetTime();
	double startTime = glfwGetTime();
	_deltaTime = startTime - lastTime;
	lastTime = startTime;

	return _deltaTime;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}