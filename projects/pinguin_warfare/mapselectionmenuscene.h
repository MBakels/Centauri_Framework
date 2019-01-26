#ifndef MAPSELECTIONMENUSCENE_H
#define MAPSELECTIONMENUSCENE_H

#include "scene.h"
#include "ui/button.h"

class MapSelectionMenuScene : public Scene {
public:
	// Constructor of the MapSelectionMenuScene class
	MapSelectionMenuScene();
	// Destructor of the MapSelectionMenuScene class
	virtual ~MapSelectionMenuScene();

	// Updates the selection menu scene
	void Update();

private:
	// Buttons to game maps
	std::vector<Button*> mapButtons;

};

#endif