#include "playership.h"

PlayerShip::PlayerShip() : GameObject() {
	addSprite("assets/ship.tga");
	position = Vector2(100, (SHEIGHT / 2));

	speed = 300.0f;
}

PlayerShip::~PlayerShip() {
	
}

void PlayerShip::update(float deltaTime) {
	// Player movement
	if (position.y > 0 && input()->getKey(KeyCode::W)) {
		position.y -= speed * deltaTime;
	}
	if (position.x > 0 && input()->getKey(KeyCode::A)) {
		position.x -= speed * deltaTime;
	}
	if (position.y < SHEIGHT && input()->getKey(KeyCode::S)) {
		position.y += speed * deltaTime;
	}
	if (position.x < SWIDTH && input()->getKey(KeyCode::D)) {
		position.x += speed * deltaTime;
	}
}