#ifndef TIME_H
#define TIME_H

// Include headers
#include <iostream>
#include <glfw/glfw3.h>

// The Time class is responsible for everything time related
class Time {
public:
	// Update the Time class
	static void Update();

	// Get the DeltaTime, deltaTime is multiplied by timeScale
	static const float DeltaTime() { return deltaTime * timeScale; };

	// timeScale controlles the flow of time and can be used to pause the game or accelerate it
	static float timeScale;

private:
	// The Constructor is private, no instance is allowed to be made
	Time() {};

	// Private deltaTime
	static float deltaTime;
};

#endif
