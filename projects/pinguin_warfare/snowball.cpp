#include "snowball.h"

SnowBall::SnowBall(Vector2 direction) {
	// Add the snowball sprite
	AddSprite("assets/SnowBall.png");
	// Setup the variables
	moveDirection = direction;
	moveSpeed = 250;
}

SnowBall::~SnowBall() {

}

void SnowBall::Update() {
	// Move the snowball
	position += moveDirection * moveSpeed * Time::DeltaTime();
}