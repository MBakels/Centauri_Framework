#include "player.h"

Player::Player(int xPos, int yPos) : Pinguin() {
	position = Vector3(xPos, yPos, 5);
}

Player::~Player() {

}

void Player::Update() {
	if (GetInput()->GetMouseDown(0)) {

	}
}