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
	Button* startButton;

};

#endif