#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"
#include "map.h"

class GameScene : public Scene {
public:
	GameScene();
	virtual ~GameScene();

	virtual void Update();

private:
	Map* map;

};

#endif
