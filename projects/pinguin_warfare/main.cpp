#include <filesystem>

#include "core.h"
#include "map.h"
#include "mainmenuscene.h"
#include "mapselectionmenuscene.h"
#include "deathmenuscene.h"
#include "winmenuscene.h"

int main() {
	// Core instance
	Core core;

	// Create menu scenes and add them to SceneMaganger
	SceneMaganger::AddScene(new MainMenuScene());
	SceneMaganger::AddScene(new MapSelectionMenuScene());
	SceneMaganger::AddScene(new WinMenuScene());
	SceneMaganger::AddScene(new DeathMenuScene());

	// Get the maps from a folder
	std::string path = "maps"; // folder path
	for (auto & map : std::filesystem::directory_iterator(path)) {
		// Create scene from path
		SceneMaganger::AddScene(new Map(map.path().string()));
	}

	// Loading the first scene (menu scene)
	SceneMaganger::LoadScene(0);

	// Run the game while the core state is running
	while (core.IsRunning()) {
		core.Run();
	}

	return 0;
}