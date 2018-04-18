#include "enemyship.h"

EnemyShip::EnemyShip(Point2 pos) : GameObject() {
	ship = new Sprite("assets/ship.tga");
	addSprite(ship);
	position = pos;
	rotation.z = PI;

	speed = 300.0f;
}

EnemyShip::~EnemyShip() {
	delete ship;
}

void EnemyShip::update(float deltaTime) {
	position.x -= speed * deltaTime;
}