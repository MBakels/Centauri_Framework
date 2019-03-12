#include "mapmakerselectionscene.h"
#include "scenemanager.h"
#include "map.h"
#include "mapmaker.h"

MapMakerSelectionScene::MapMakerSelectionScene() {
	// Create new map button
	newMapButton = new Button(Point3(200, 100, 0), "assets/WhiteSquare.png", BLACK);
	newMapButton->GetSprite()->size = Point2(300, 100);
	newMapButton->AddButtonText("New map", 0, 0, 62);
	AddChild(newMapButton);

	// Initial button position
	int xPos = 550, yPos = 100;
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

	// Create newMapMenu
	newMapMenu = new GameObject();
	newMapMenu->AddSprite("assets/WhiteSquare.png");
	newMapMenu->GetSprite()->color = BLACK;
	newMapMenu->GetSprite()->size = Point3(320, 190, 1);
	newMapMenu->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	newMapMenu->SetActive(false);
	AddChild(newMapMenu);

	// Create and add all menu components to newMapMenu
	mapNameInput = new InputField(Point3(0, -60, 2), Point2(300, 50), "Name");
	newMapMenu->AddChild(mapNameInput);

	mapSizeXInput = new InputField(Point3(-50, 0, 2), Point2(100, 50), "10");
	newMapMenu->AddChild(mapSizeXInput);

	mapSizeXText = new GameObject();
	mapSizeXText->AddText("X", "fonts/acari-sans/AcariSans-Regular.ttf", 48, WHITE);
	mapSizeXText->position = Point3(-140, -20, 2);
	newMapMenu->AddChild(mapSizeXText);

	mapSizeYInput = new InputField(Point3(100, 0, 2), Point2(100, 50), "10");
	newMapMenu->AddChild(mapSizeYInput);

	mapSizeYText = new GameObject();
	mapSizeYText->AddText("Y", "fonts/acari-sans/AcariSans-Regular.ttf", 48, WHITE);
	mapSizeYText->position = Point3(10, -20, 2);
	newMapMenu->AddChild(mapSizeYText);

	createMapButton = new Button(Point3(0, 60, 2), "assets/WhiteSquare.png", WHITE);
	createMapButton->GetSprite()->size = Point2(300, 50);
	createMapButton->AddButtonText("Create map", 0, 0, 48);
	createMapButton->buttonText->GetText()->color = BLACK;
	newMapMenu->AddChild(createMapButton);

}

MapMakerSelectionScene::~MapMakerSelectionScene() {
	// Removing the new map button
	RemoveChild(newMapButton);
	delete newMapButton;

	// Removing new map menu items
	RemoveChild(newMapMenu);
	delete newMapMenu;
	RemoveChild(mapNameInput);
	delete mapNameInput;
	RemoveChild(mapSizeXInput);
	delete mapSizeXInput;
	RemoveChild(mapSizeYInput);
	delete mapSizeYInput;
	RemoveChild(mapSizeXText);
	delete mapSizeXText;
	RemoveChild(mapSizeYText);
	delete mapSizeYText;
	RemoveChild(createMapButton);
	delete createMapButton;

	// Remove all map buttons
	std::vector<Button*>::iterator buttonsIt;
	for (buttonsIt = mapButtons.begin(); buttonsIt != mapButtons.end(); buttonsIt++) {
		RemoveChild((*buttonsIt));
		delete (*buttonsIt);
	}
	mapButtons.clear();
}

void MapMakerSelectionScene::Update() {
	if (!newMapMenu->isActive) {
		if (newMapButton->CheckPressed(Point2(GetInput()->GetMouseX(), GetInput()->GetMouseY()))) {
			newMapMenu->SetActive(true);
		}

		// Check button input for each map button
		for each(Button* button in mapButtons) {
			if (button->CheckPressed(Point2(GetInput()->GetMouseX(), GetInput()->GetMouseY()))) {
				// If the button is pressed create a new map and load it
				std::cout << "Selected map name is: " << button->buttonText->GetText()->text << std::endl;
				//SceneMaganger::AddScene(new Map(button->buttonText->GetText()->text));
				//SceneMaganger::LoadScene(4);
			}
		}
	} else {
		if (GetInput()->GetMouseDown(0)) {
			Point2 halfSize = newMapMenu->GetSprite()->size / 2;
			float mousePosX = GetInput()->GetMouseX();
			float mousePosY = GetInput()->GetMouseY();
			if (!(mousePosX <= newMapMenu->position.x + halfSize.x && mousePosX > newMapMenu->position.x - halfSize.x && mousePosY <= newMapMenu->position.y + halfSize.y && mousePosY > newMapMenu->position.y - halfSize.y)) {
				newMapMenu->SetActive(false);
				return;
			}
		}
		// Check if the create new map button is pressed
		if (createMapButton->CheckPressed(Point2(GetInput()->GetMouseX(), GetInput()->GetMouseY()))) {
			// Check input fields
			std::cout << "Creating new map " << std::endl;
		}
	}
}
