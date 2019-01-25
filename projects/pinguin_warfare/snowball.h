#ifndef SNOWBALL_H
#define SNOWBALL_H

#include "gameobject.h"

class SnowBall : public GameObject {
public:
	// Constructor of the SnowBall class
	SnowBall(Vector2 startPos, Vector2 direction, bool thrownByPlayer);
	// Destructor of the SnowBall class
	virtual ~SnowBall();

	// Updates the snowball gameobject
	void Update();

	// Is this snowball thrown by the player
	bool ThrownByPlayer() { return thrownByPlayer; };

private:
	Vector2 moveDirection; // Direction to move in
	int moveSpeed; // Movement speed
	bool thrownByPlayer; // Is this snowball thrown by the player
};

#endif
