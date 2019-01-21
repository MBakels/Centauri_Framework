#include "math/time.h"

// Set static variables
float Time::deltaTime = 0;
float Time::timeScale = 1;

void Time::Update() {
	// Calculate deltaTime
	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
}
