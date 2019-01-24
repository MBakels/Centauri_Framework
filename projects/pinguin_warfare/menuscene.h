#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "scene.h"
#include "ui/button.h"

class MenuScene : public Scene {
public:
	// Constructor of the MenuScene class
	MenuScene();
	// Destructor of the MenuScene class
	virtual ~MenuScene();

	// Updates the menu scene
	void Update();

private:
	// Menu buttons
	Button* startButton;
	Button* mapBuilderButton;
	Button* quitButton;

};

#endif