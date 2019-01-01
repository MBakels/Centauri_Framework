#include "math/time.h"

float Time::deltaTime = 0;

void Time::Update() {
	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
}
