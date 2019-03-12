#include "mapselectionmenuscene.h"
#include "scenemanager.h"
#include "map.h"

MapSelectionMenuScene::MapSelectionMenuScene() {
	// Initial button position
	int xPos = 200, yPos = 100;
	// Add a button for each MapData element in maps
	for each(std::pair<std::string, MapData*> map in Map::maps) {
		// Create and add button
		Button* mapButton = new Button(Point3(xPos, yPos, 0), "assets/WhiteSquare.png", BLACK);
		mapButton->GetSprite()->size = Point2(300, 100);
		mapButton->AddButtonText(map.first, 0, 0, 62);
		AddChild(mapButton);
		// Add button to buttons vector
		mapButtons.push_back(mapButton);
		// Set position for next button
		xPos += 350;
		if (xPos >= SWIDTH - 175) {
			yPos += 150;
			xPos = 200;
		}
	}
}

MapSelectionMenuScene::~MapSelectionMenuScene() {
	// Remove all buttons
	std::vector<Button*>::iterator buttonsIt;
	for (buttonsIt = mapButtons.begin(); buttonsIt != mapButtons.end(); buttonsIt++) {
		RemoveChild((*buttonsIt));
		delete (*buttonsIt);
	}
	mapButtons.clear();
}

void MapSelectionMenuScene::Update() {
	// Check button input for each button
	for each(Button* button in mapButtons) {
		if (button->CheckPressed(Point2(GetInput()->GetMouseX(), GetInput()->GetMouseY()))) {
			// If the button is pressed create a new map and load it
			SceneMaganger::AddScene(new Map(button->buttonText->GetText()->text));
			SceneMaganger::LoadScene(5);
		}
	}
}