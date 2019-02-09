#include "core.h"

#include "gamescene.h"

int main() {

	Core core;

	// Create game scene and add it to SceneMaganger
	SceneMaganger::AddScene(new GameScene());

	// Loading the first scene (menu scene)
	SceneMaganger::LoadScene(0);

	// Run the game while the core state is running
	while (core.IsRunning()) {
		core.Run();
	}

	return 0;
}