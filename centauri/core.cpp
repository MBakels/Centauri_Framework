#include "core.h"

Core::Core() {
	_deltaTime = 0;
	_running = true;
}

Core::~Core() {

}

void Core::Run(Scene* scene) {
	// update our _deltaTime
	CalculateDeltaTime();

	// Input
	//glfwPollEvents();
	//processInput(_renderer.window());
	Singleton<Input>::Instance()->UpdateInput(_renderer.GetWindow());

	// Update camera instance in Scene
	scene->GetCamera()->UpdateCamera();

	// Update Scene (and recursively all children)
	scene->UpdateScene((float)_deltaTime);

	// Render Scene
	_renderer.RenderScene(scene);

	if (glfwWindowShouldClose(_renderer.GetWindow()) == 1) { _running = false; }
}

void Core::ShowFrameRate(float numsecs) {
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

double Core::CalculateDeltaTime() {
	static double lastTime = glfwGetTime();
	double startTime = glfwGetTime();
	_deltaTime = startTime - lastTime;
	lastTime = startTime;

	return _deltaTime;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void Core::ProcessInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
