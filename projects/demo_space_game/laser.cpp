#include "laser.h"

Laser::Laser(Point3 pos) : GameObject() {
	laser = new Sprite("assets/laser.tga");
	addSprite(laser);
	position = pos;

	scale = Vector2(6, 0.7);

	speed = 600.0f;
}

Laser::~Laser() {
	delete laser;
}

void Laser::update(float deltaTime) {
	position.x += speed * deltaTime;
}