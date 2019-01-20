#include "pinguin.h"

Pinguin::Pinguin() : GameObject() {
	AddSprite("assets/pinguin.png");
	moveDirection = Vector2(0, 0);
	targetPos = Point2(0, 0);
	moveSpeed = 150;
}

Pinguin::~Pinguin() {

}

void Pinguin::Update() {
	if (moveDirection != Vector2(0, 0)) {
		position += moveDirection * moveSpeed * Time::DeltaTime();
		if (moveDirection.x > 0 && position.x >= targetPos.x) {
			TargetPosReached();
		} else if (moveDirection.x < 0 && position.x <= targetPos.x) {
			TargetPosReached();
		} else if (moveDirection.y > 0 && position.y >= targetPos.y) {
			TargetPosReached();
		} else if (moveDirection.y < 0 && position.y <= targetPos.y) {
			TargetPosReached();
		}
	}
}

void Pinguin::MoveTo(Point2 tilePos, Vector2 direction) {
	x = tilePos.x;
	y = tilePos.y;
	targetPos = tilePos * 64;
	moveDirection = direction;
}

void Pinguin::TargetPosReached() {
	moveDirection = Vector2(0, 0);
	position.x = targetPos.x;
	position.y = targetPos.y;
}