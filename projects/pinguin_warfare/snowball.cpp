#include "snowball.h"

SnowBall::SnowBall(Vector2 startPos,Vector2 direction, bool thrownByPlayer) {
	// Add the snowball sprite
	AddSprite("assets/SnowBall.png");
	// Setup the variables
	position = startPos;
	position.z = 2;
	moveDirection = direction;
	moveSpeed = 250;
	this->thrownByPlayer = thrownByPlayer;
}

SnowBall::~SnowBall() {

}

void SnowBall::Update() {
	// Move the snowball
	position += moveDirection * moveSpeed * Time::DeltaTime();
}