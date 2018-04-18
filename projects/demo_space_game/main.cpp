#include "core.h"

#include "gamescene.h"

int main() {

	Core core;

	GameScene* gameScene = new GameScene();

	while (core.isRunning()) {
		core.run(gameScene);
		//core.showFrameRate(5);
	}
	delete gameScene;

	return 0;
}