#ifndef TILE_H
#define TILE_H

#include "gameobject.h"

enum TileBehaviour {
	Solid,			// The Tile is solid you can't move on top of it
	SlowDown,		// The Tile will stop movement when you move over top of it
	Slide			// The Tile wil not alter movement you wil keep sliding
};

class Tile : public GameObject {
public:
	Tile(int x, int y, int type);
	virtual ~Tile();

	int x, y;
	TileBehaviour tileBehaviour;

private:

};

#endif
