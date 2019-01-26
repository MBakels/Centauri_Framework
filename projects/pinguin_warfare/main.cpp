#include <filesystem>

#include "core.h"
#include "map.h"
#include "menuscene.h"

int main() {
	// Core instance
	Core core;

	// Create scenes and add them to SceneMaganger
	SceneMaganger::AddScene(new MenuScene());

	// Get the maps from a folder
	std::string path = "maps"; // folder path
	for (auto & map : std::filesystem::directory_iterator(path)) {
		// Create scene from path
		SceneMaganger::AddScene(new Map(map.path().string()));
	}

	// Loading the first scene (menu scene)
	SceneMaganger::LoadScene(0);

	while (core.IsRunning()) {
		core.Run();
	}

	return 0;
}