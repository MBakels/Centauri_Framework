#include "tile.h"

Tile::Tile(int x, int y, int type) : GameObject() {
	position = Vector3(x * 64, y * 64, 0);
	this->x = x;
	this->y = y;
	AddSpriteSheet("assets/tileset.png", 2, 2);

	switch (type) {
		case 1:
			GetSprite()->Frame(2);
			tileBehaviour = TileBehaviour::Slide;
			break;
		case 2:
			GetSprite()->Frame(3);
			tileBehaviour = TileBehaviour::SlowDown;
			break;
		case 3:
			GetSprite()->Frame(1);
			tileBehaviour = TileBehaviour::Solid;
			break;
	}
}

Tile::~Tile() {
	
}

