#include "core.h"

Core::Core() {
	_running = true;
}

Core::~Core() {

}

void Core::Run(Scene* scene) {
	// Update Time
	Time::Update();

	// Input
	Singleton<Input>::Instance()->UpdateInput(_renderer.GetWindow());

	// Update current Scene
	scene->UpdateScene();

	// Render Scene
	_renderer.RenderScene(scene);

	if (glfwWindowShouldClose(_renderer.GetWindow()) == 1) { _running = false; }
}

/*
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
*/
