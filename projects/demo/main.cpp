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
	/*
	Camera* camera = new Camera(); // Creater camera

	// Create sprites
	Sprite* wood = new Sprite("assets/container.tga");
	Sprite* pencils = new Sprite("assets/pencils.tga");
	Sprite* kingkong = new Sprite("assets/kingkong.tga");

	GameObject* woodObj = new GameObject();
	woodObj->AddSprite(wood);
	woodObj->position = Vector2(220, 220);
	woodObj->scale = Vector2(0.7f, 0.7f);

	GameObject* pencilsObj = new GameObject();
	pencilsObj->AddSprite(pencils);
	pencilsObj->position = Vector2(500, 100);

	GameObject* kingkongObj = new GameObject();
	kingkongObj->AddSprite(kingkong);
	kingkongObj->position = Vector2(750, 500);
	kingkongObj->scale = Vector2(2.0f, 2.0f);
	*/

	Scene00* scene00 = new Scene00();

	while (!glfwWindowShouldClose(renderer.Window())) {
		processInput(renderer.Window()); // Input

		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear screen

		CalculateDeltaTime();

		scene00->GetCamera()->UpdateCamera(); // Update camera

		//renderer.RenderEntity(glm::mat4(1.0f), woodObj, camera);
		//renderer.RenderEntity(glm::mat4(1.0f), pencilsObj, camera);
		//renderer.RenderEntity(glm::mat4(1.0f), kingkongObj, camera);

		scene00->UpdateScene(_deltaTime);
		renderer.RenderScene(scene00);

		// glfw: swap buffers and poll IO events
		//glfwSwapBuffers(renderer.window());
		glfwPollEvents();
	}
	// Delete all resources once they've outlived their purpose
	//delete camera;
	//delete wood;
	//delete pencils;
	//delete kingkong;
	//delete woodObj;

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