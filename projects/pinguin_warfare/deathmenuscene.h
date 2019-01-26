#ifndef DEATHMENUSCENE_H
#define DEATHMENUSCENE_H

#include "scene.h"
#include "ui/button.h"

class DeathMenuScene : public Scene {
public:
	// Constructor of the DeathMenuScene class
	DeathMenuScene();
	// Destructor of the DeathMenuScene class
	virtual ~DeathMenuScene();

	// Updates the death menu scene
	void Update();

private:
	// Menu button
	Button * menuButton;

	// Text massage
	GameObject* text;

};

#endif