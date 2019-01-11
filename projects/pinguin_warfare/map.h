#ifndef MAP_H
#define MAP_H

#include "gameobject.h"
#include "tile.h"

class Map : public GameObject {
public:
	Map(int width, int height, std::vector<int> tiles);
	virtual ~Map();

	int Width() { return width; }
	int Height() { return height; }

private:
	int width;
	int height;

	std::vector<Tile*> tiles;

};

#endif