#ifndef PINGUIN_H
#define PINGUIN_H

#include "gameobject.h"

class Pinguin : public GameObject {
public:
	// Constructor of the Pinguin class
	Pinguin(int xPos, int yPos, int zPos);
	// Destructor of the Pinguin class
	virtual ~Pinguin();

	// Updates the pinguin gameobject
	void Update();

	// Sets the position to move to
	void MoveTo(Point2 tilePos, Vector2 direction);

	// Returns true if the pinguin is moving
	bool IsMoving() { return (moveDirection != Vector2(0, 0)) ? true : false; };

	// Returns true if the pinguin is alive
	bool IsAlive() { return (lives > 0); };

	// Removes a live
	void RemoveLive() { lives--; };

	// Can the pinguin throw a snowball
	bool CanThrow() { return (throwTimer >= timeBetweenThrows); };

	// A snowball has been thrown
	void SnowBallThrown() { throwTimer = 0; };

	int x, y; // Position in the Map grid

private:
	Vector2 moveDirection; // Direction to move in
	Point2 targetPos; // Target position
	int moveSpeed; // Movement speed
	int lives; // Lives of the pinguin
	float throwTimer; // Keeps track of time sinds last snowball throw
	float timeBetweenThrows; // Time between throws

	// This method is called when the pinguin has reached the targetPos and stops movement
	void TargetPosReached();

};

#endif
