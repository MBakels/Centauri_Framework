#ifndef SNOWBALL_H
#define SNOWBALL_H

#include "gameobject.h"

class SnowBall : public GameObject {
public:
	// Constructor of the SnowBall class
	SnowBall(Vector2 direction);
	// Destructor of the SnowBall class
	virtual ~SnowBall();

	// Updates the snowball gameobject
	void Update();

private:
	Vector2 moveDirection; // Direction to move in
	int moveSpeed; // Movement speed
};

#endif
