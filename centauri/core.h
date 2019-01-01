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

	void Run(Scene* scene);

	//void ShowFrameRate(float numsecs);

	bool IsRunning() { return _running; };

private:
	Renderer _renderer;
	bool _running;

};

#endif