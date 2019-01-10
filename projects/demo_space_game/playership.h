#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include "gameobject.h"

class PlayerShip : public GameObject {
public:
	PlayerShip();
	virtual ~PlayerShip();

	virtual void Update();

private:
	Sprite* ship;

	float speed;
};

#endif