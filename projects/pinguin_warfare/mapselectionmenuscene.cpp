#include "mapselectionmenuscene.h"
#include "scenemanager.h"

MapSelectionMenuScene::MapSelectionMenuScene() {
	// Start game button
	menuButton = new Button(Point2(SWIDTH / 2, SHEIGHT / 2 + 100, 10), "assets/StartGameButton.png");
	AddChild(menuButton);
}

MapSelectionMenuScene::~MapSelectionMenuScene() {
	// Removing created objects
	RemoveChild(menuButton);
	delete menuButton;
}

void MapSelectionMenuScene::Update() {
	// Check button input
	if (menuButton->CheckPressed(Point2(GetInput()->GetMouseX(), GetInput()->GetMouseY()))) {
		SceneMaganger::LoadScene(0);
	}
}