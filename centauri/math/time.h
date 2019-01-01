#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <glfw/glfw3.h>

class Time {
public:
	static void Update();

	static const float DeltaTime() { return deltaTime; };

private:
	Time() {};

	static float deltaTime;
};

#endif
