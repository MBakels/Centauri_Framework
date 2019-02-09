#include "core.h"

#include "scene01.h"
#include "scene02.h"
#include "scene03.h"

int main() {
	// Core instance
	Core core;

	// Create demo scenes and add them to SceneMaganger
	SceneMaganger::AddScene(new Scene01());
	SceneMaganger::AddScene(new Scene02());
	SceneMaganger::AddScene(new Scene03());

	// Loading the first scene (menu scene)
	SceneMaganger::LoadScene(0);

	// Run the game while the core state is running
	while (core.IsRunning()) {
		core.Run();
	}

	return 0;
}
