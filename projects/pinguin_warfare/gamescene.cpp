#include "gamescene.h"

GameScene::GameScene() : Scene() {
	int mapSizeX = 10;
	int mapSizeY = 10;

	// Map layout
	std::vector<int> tiles{
		2,2,2,2,2,2,2,2,2,2,
		2,1,1,1,1,1,2,1,1,2,
		2,1,1,2,1,1,1,1,1,2,
		2,1,1,1,1,1,1,2,1,2,
		2,1,1,2,2,1,1,1,1,2,
		2,1,1,1,2,1,1,1,1,2,
		2,1,1,1,1,1,2,1,1,2,
		2,1,1,1,2,1,1,2,1,2,
		2,1,1,1,1,1,1,1,1,2,
		2,2,2,2,2,2,2,2,2,2
	};
	/*
	std::vector<int> tiles;
	for (int i = 0; i < mapSizeX * mapSizeY; i++) {
		tiles.push_back(1);
	}
	*/
	map = new Map(mapSizeX, mapSizeY, tiles);
	AddChild(map);
}

GameScene::~GameScene() {
	delete map;
}

void GameScene::Update() {
	if (GetInput()->GetKey(KeyCode::EscapeKey)) {
		GetInput()->ExitApplication();
	}
	if (GetInput()->GetMouseDown(0)) {
		map->GetMaxDistanceInDirectionTravelable(Point2(GetInput()->GetMouseX(), GetInput()->GetMouseY()), Direction::North);
	}
	//std::cout << map->GetTilePosition(Point2(GetInput()->GetMouseX(), GetInput()->GetMouseY())) << std::endl;
}
