#include "core.h"

Core::Core() {
	_deltaTime = 0;
	_running = true;
}

Core::~Core() {

}

void Core::run(Scene* scene) {
	// update our _deltaTime
	calculateDeltaTime();

	// Input
	//glfwPollEvents();
	//processInput(_renderer.window());
	Singleton<Input>::instance()->updateInput(_renderer.window());

	// Update camera instance in Scene
	scene->camera()->updateCamera();

	// Update Scene (and recursively all children)
	scene->updateScene((float)_deltaTime);

	// Render Scene
	_renderer.renderScene(scene);

	if (glfwWindowShouldClose(_renderer.window()) == 1) { _running = false; }
}

void Core::showFrameRate(float numsecs) {
	static int frames = 0;
	static double time = 0;

	frames++;
	time += _deltaTime;
	if (time >= numsecs) {
		printf("%f ms/frame (%f FPS)\n", (numsecs * 1000) / double(frames), frames / numsecs);
		frames = 0;
		time = 0;
	}
}

double Core::calculateDeltaTime() {
	static double lastTime = glfwGetTime();
	double startTime = glfwGetTime();
	_deltaTime = startTime - lastTime;
	lastTime = startTime;

	return _deltaTime;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void Core::processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
