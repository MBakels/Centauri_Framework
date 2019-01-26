#ifndef WINMENUSCENE_H
#define WINMENUSCENE_H

#include "scene.h"
#include "ui/button.h"

class WinMenuScene : public Scene {
public:
	// Constructor of the WinMenuScene class
	WinMenuScene();
	// Destructor of the WinMenuScene class
	virtual ~WinMenuScene();

	// Updates the win menu scene
	void Update();

private:
	// Menu button
	Button * menuButton;

	// Text massage
	GameObject* text;
};

#endif