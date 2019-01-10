#include "enemyship.h"

EnemyShip::EnemyShip(Point2 pos) : GameObject() {
	AddSprite("assets/ship.tga");
	position = pos;
	rotation.z = PI;

	speed = 300.0f;
}

EnemyShip::~EnemyShip() {

}

void EnemyShip::Update() {
	position.x -= speed * Time::DeltaTime();
}