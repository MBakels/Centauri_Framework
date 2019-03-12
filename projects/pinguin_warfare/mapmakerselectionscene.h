#ifndef MAPMAKERSELECTIONSCENE_H
#define MAPMAKERSELECTIONSCENE_H

#include "scene.h"
#include "ui/button.h"
#include "ui/inputfield.h"

class MapMakerSelectionScene : public Scene {
public:
	// Constructor of the MapSelectionMenuScene class
	MapMakerSelectionScene();
	// Destructor of the MapSelectionMenuScene class
	virtual ~MapMakerSelectionScene();

	// Updates the selection menu scene
	void Update();

private:
	// Buttons to game maps
	std::vector<Button*> mapButtons;
	// Button for creating a new map
	Button* newMapButton;
	// The menu for creating a new map
	GameObject* newMapMenu;
	InputField* mapNameInput;
	InputField* mapSizeXInput;
	InputField* mapSizeYInput;
	GameObject* mapSizeXText;
	GameObject* mapSizeYText;

};

#endif