#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "gameobject.h"
#include "ui/button.h"

class PauseMenu : public GameObject {
public:
	// Constructor of the PauseMenu class
	PauseMenu();
	// Destructor of the PauseMenu class
	virtual ~PauseMenu();

	// Updates the pausemenu scene
	void Update(Point2 cameraPos);

	// Toggle the pause menu
	void Toggle();

private:
	// Menu buttons
	Button * resumeButton;
	Button* menuButton;

};

#endif
