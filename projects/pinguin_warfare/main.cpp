#include "core.h"

#include "gamescene.h"

int main() {

	Core core;

	GameScene* gameScene = new GameScene();

	while (core.IsRunning()) {
		core.Run(gameScene);
	}

	delete gameScene;

	return 0;
}