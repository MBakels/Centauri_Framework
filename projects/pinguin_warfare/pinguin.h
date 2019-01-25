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

	// Removes a live
	void RemoveLive() { lives--; };

	int x, y; // Position in the Map grid

private:
	Vector2 moveDirection; // Direction to move in
	Point2 targetPos; // Target position
	int moveSpeed; // Movement speed
	int lives; // Lives of the pinguin

	// This method is called when the pinguin has reached the targetPos and stops movement
	void TargetPosReached();

};

#endif
