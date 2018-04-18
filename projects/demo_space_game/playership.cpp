#include "playership.h"

PlayerShip::PlayerShip() : GameObject() {
	ship = new Sprite("assets/ship.tga");
	addSprite(ship);
	position = Vector2(100, (SHEIGHT / 2));

	speed = 200.0f;
}

PlayerShip::~PlayerShip() {
	delete ship;
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