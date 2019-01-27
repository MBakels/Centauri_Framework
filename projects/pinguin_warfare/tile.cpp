#include "tile.h"

Tile::Tile(int x, int y, int type) {
	// Setup the variables
	position = Point3(x * 64, y * 64, 0);
	this->x = x;
	this->y = y;
	topLayer = NULL;
	// Setup the spritesheet
	AddSpriteSheet("assets/Tileset.png", 2, 2);

	// Check the type of this tile, set the frame of the spritesheet to match the type and set the TileBehaviour
	switch (type) {
		case 1:
			// Ice tile
			GetSprite()->Frame(2);
			tileBehaviour = TileBehaviour::Slide;
			break;
		case 2:
			// Snow tile
			GetSprite()->Frame(3);
			tileBehaviour = TileBehaviour::SlowDown;
			break;
		case 3:
			// Ice stalagmite tile
			GetSprite()->Frame(2);
			topLayer = new GameObject();
			topLayer->position.z = 1;
			topLayer->AddSprite("assets/Stalagmite.png");
			AddChild(topLayer);
			tileBehaviour = TileBehaviour::Solid;
			break;
	}
}

Tile::~Tile() {
	if (topLayer != NULL) {
		RemoveChild(topLayer);
		delete topLayer;
	}
}

