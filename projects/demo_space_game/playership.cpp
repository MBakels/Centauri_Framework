#include "playership.h"

PlayerShip::PlayerShip() : GameObject() {
	AddSprite("assets/ship.tga");
	position = Vector2(100, (SHEIGHT / 2));

	speed = 300.0f;
}

PlayerShip::~PlayerShip() {
	
}

void PlayerShip::Update(float deltaTime) {
	// Player movement
	if (position.y > 0 && GetInput()->GetKey(KeyCode::W)) {
		position.y -= speed * deltaTime;
	}
	if (position.x > 0 && GetInput()->GetKey(KeyCode::A)) {
		position.x -= speed * deltaTime;
	}
	if (position.y < SHEIGHT && GetInput()->GetKey(KeyCode::S)) {
		position.y += speed * deltaTime;
	}
	if (position.x < SWIDTH && GetInput()->GetKey(KeyCode::D)) {
		position.x += speed * deltaTime;
	}
}