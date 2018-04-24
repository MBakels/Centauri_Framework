#include "enemyship.h"

EnemyShip::EnemyShip(Point2 pos) : GameObject() {
	addSprite("assets/ship.tga");
	position = pos;
	rotation.z = PI;

	speed = 300.0f;
}

EnemyShip::~EnemyShip() {

}

void EnemyShip::update(float deltaTime) {
	position.x -= speed * deltaTime;
}