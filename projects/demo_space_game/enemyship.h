#ifndef ENEMY_H
#define ENEMY_H

#include "gameobject.h"

class EnemyShip : public GameObject {
public:
	EnemyShip(Point2 pos);
	virtual ~EnemyShip();

	virtual void update(float deltaTime);

private:
	float speed;
};

#endif