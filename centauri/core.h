#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "renderer.h"
#include "gameobject.h"
#include "scene.h"

#include <GLFW/glfw3.h>

class Core {
public:
	Core();
	virtual ~Core();

	void run(Scene* scene);

	float deltaTime() { return (float)_deltaTime; };

	void showFrameRate(float numsecs);

	bool isRunning() { return _running; };

private:
	Renderer _renderer;
	double _deltaTime;
	bool _running;

	double calculateDeltaTime();

	void processInput(GLFWwindow *window);

};

#endif