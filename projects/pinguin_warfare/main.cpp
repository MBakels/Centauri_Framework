#include "core.h"

#include "map.h"
#include "menuscene.h"

int main() {
	// Core instance
	Core core;

	// Create scenes and add them to SceneMaganger
	SceneMaganger::AddScene(new MenuScene());
	SceneMaganger::AddScene(new Map("maps/test.m"));

	// Loading the first scene (menu scene)
	SceneMaganger::LoadScene(0);

	while (core.IsRunning()) {
		core.Run();
	}

	return 0;
}