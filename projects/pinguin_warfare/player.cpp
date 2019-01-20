#include "player.h"

Player::Player(int xPos, int yPos) : Pinguin() {
	position = Vector3(xPos * 64, yPos * 64, 5);
	x = xPos;
	y = yPos;
}

Player::~Player() {

}

void Player::Update() {
	
}