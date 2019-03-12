#include <filesystem>

#include "core.h"
#include "map.h"
#include "mainmenuscene.h"
#include "mapselectionmenuscene.h"
#include "deathmenuscene.h"
#include "winmenuscene.h"
#include "mapmakerselectionscene.h"

int main() {
	// Core instance
	Core core;

	// Get the maps from a folder
	std::string path = "maps"; // folder path
	for (auto & map : std::filesystem::directory_iterator(path)) {
		// Load map
		Map::LoadMap(map.path().string());
	}

	// Create menu scenes and add them to SceneMaganger
	SceneMaganger::AddScene(new MainMenuScene());
	SceneMaganger::AddScene(new MapSelectionMenuScene());
	SceneMaganger::AddScene(new WinMenuScene());
	SceneMaganger::AddScene(new DeathMenuScene());
	SceneMaganger::AddScene(new MapMakerSelectionScene());

	// Loading the first scene (menu scene)
	SceneMaganger::LoadScene(0);

	// Run the game while the core state is running
	while (core.IsRunning()) {
		core.Run();
	}

	return 0;
}