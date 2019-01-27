#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include "scene.h"
#include "ui/button.h"

class MainMenuScene : public Scene {
public:
	// Constructor of the MainMenuScene class
	MainMenuScene();
	// Destructor of the MainMenuScene class
	virtual ~MainMenuScene();

	// Gets called after SceneManager loads the scene
	void SceneLoaded();

	// Updates the menu scene
	void Update();

private:
	// Menu buttons
	Button* startButton;
	//Button* mapBuilderButton;
	Button* quitButton;

};

#endif