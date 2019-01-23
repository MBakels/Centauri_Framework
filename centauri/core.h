#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "renderer.h"
#include "scenemanager.h"

#include <GLFW/glfw3.h>

class Core {
public:
	Core();
	virtual ~Core();

	void Run();

	bool IsRunning() { return _running; };

private:
	Renderer _renderer;
	SceneMaganger _scenemanager;
	bool _running;

};

#endif