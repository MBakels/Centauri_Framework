#include "tile.h"

Tile::Tile(int x, int y, int type) {
	// Setup the variables
	position = Point3(x * 64, y * 64, 0);
	this->x = x;
	this->y = y;
	topLayer = NULL;

	// Check the type of this tile, set the frame of the spritesheet to match the type and set the TileBehaviour
	switch (type) {
		case 1:
			// Ice tile
			AddSprite("assets/IceTile.png");
			tileBehaviour = TileBehaviour::Slide;
			break;
		case 2:
			// Snow tile
			AddSprite("assets/SnowTile.png");
			tileBehaviour = TileBehaviour::SlowDown;
			break;
		case 3:
			// Ice stalagmite tile
			AddSprite("assets/IceTile.png");
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

