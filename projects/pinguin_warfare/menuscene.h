#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "scene.h"
#include "ui/button.h"

class MenuScene : public Scene {
public:
	MenuScene();
	virtual ~MenuScene();

	void Update();

private:
	// Menu buttons
	Button* startButton;
	Button* mapBuilderButton;
	Button* quitButton;

};

#endif