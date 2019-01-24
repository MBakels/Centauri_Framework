#include "pinguin.h"

Pinguin::Pinguin(int xPos, int yPos, int zPos) {
	// Add the pinguin sprite
	AddSprite("assets/pinguin.png");
	// Setup the variables
	moveDirection = Vector2(0, 0);
	targetPos = Point2(0, 0);
	moveSpeed = 150;
	position = Point3(xPos * 64, yPos * 64, zPos);
	x = xPos;
	y = yPos;
	lives = 5;
}

Pinguin::~Pinguin() {

}

void Pinguin::Update() {
	// Check if we should move
	if (moveDirection != Vector2(0, 0)) {
		// Update position and check if targetPos is reached
		position += moveDirection * moveSpeed * Time::DeltaTime();
		if (moveDirection.x > 0 && position.x >= targetPos.x) {
			TargetPosReached();
		} else if (moveDirection.x < 0 && position.x <= targetPos.x) {
			TargetPosReached();
		} else if (moveDirection.y > 0 && position.y >= targetPos.y) {
			TargetPosReached();
		} else if (moveDirection.y < 0 && position.y <= targetPos.y) {
			TargetPosReached();
		}
	}
}

void Pinguin::MoveTo(Point2 tilePos, Vector2 direction) {
	// Setting the new tile position
	x = tilePos.x;
	y = tilePos.y;
	// Setting the targetPos
	targetPos = tilePos * 64;
	// Setting the moveDirection, and normalizing it
	moveDirection = direction.getNormalized();
}

void Pinguin::TargetPosReached() {
	// Set moveDirection to stop movement
	moveDirection = Vector2(0, 0);
	// We can overshoot the targetPos by a few pixels so set position to targetPos
	position.x = targetPos.x;
	position.y = targetPos.y;
}