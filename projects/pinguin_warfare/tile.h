#ifndef TILE_H
#define TILE_H

#include "gameobject.h"

// Behaviour of the tile with pinguins
enum TileBehaviour {
	Solid,			// The Tile is solid you can't move on top of it
	SlowDown,		// The Tile will stop movement when you move over top of it
	Slide			// The Tile wil not alter movement you wil keep sliding
};

class Tile : public GameObject {
public:
	// Constructor of the Tile class
	Tile(int x, int y, int type);
	// Destructor of the Tile class
	virtual ~Tile();

	// Position in the map grid
	int x, y;
	// Behaviour of this tile
	TileBehaviour tileBehaviour;

};

#endif
