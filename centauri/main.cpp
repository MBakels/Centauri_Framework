#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer.h"
#include "camera.h"
#include "sprite.h"

void processInput(GLFWwindow *window);

int main() {	
	Renderer renderer; // Create renderer
	Camera* camera = new Camera(); // Creater camera

	// Create sprites
	Sprite* wood = new Sprite("assets/container.tga");
	Sprite* pencils = new Sprite("assets/pencils.tga");
	Sprite* kingkong = new Sprite("assets/kingkong.tga");

	while (!glfwWindowShouldClose(renderer.window())) {
		processInput(renderer.window()); // Input

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear screen

		camera->UpdateCamera(); // Update camera

		renderer.renderSprite(camera, wood, 220, 220, 0.7f, 0.7f, 0);
		renderer.renderSprite(camera, pencils, 500, 100, 1.0f, 1.0f, 0);
		renderer.renderSprite(camera, kingkong, 750, 500, 2.0f, 2.0f, 0);

		// glfw: swap buffers and poll IO events
		glfwSwapBuffers(renderer.window());
		glfwPollEvents();
	}
	// Delete all resources once they've outlived their purpose
	delete camera;
	delete wood;
	delete pencils;
	delete kingkong;

	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
