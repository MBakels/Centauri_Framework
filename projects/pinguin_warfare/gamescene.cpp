#include "gamescene.h"

GameScene::GameScene() : Scene() {
	std::vector<int> tiles;
	for (int i = 0; i < 25; i++) {
		tiles.push_back(1);
	}
	map = new Map(5, 5, tiles);
}

GameScene::~GameScene() {
	delete map;
}

void GameScene::Update() {
	if (GetInput()->GetKey(KeyCode::EscapeKey)) {
		GetInput()->ExitApplication();
	}
}
