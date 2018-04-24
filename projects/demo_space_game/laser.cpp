#include "laser.h"

Laser::Laser(Point3 pos) : GameObject() {
	addSprite("assets/laser.tga");
	position = pos;

	scale = Vector2(6, 0.7);

	speed = 600.0f;
}

Laser::~Laser() {
	
}

void Laser::update(float deltaTime) {
	position.x += speed * deltaTime;
}