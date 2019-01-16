#ifndef MAP_H
#define MAP_H

#include "gameobject.h"
#include "tile.h"

enum Direction {
	North,
	NorthEast,
	East,
	SouthEast,
	South,
	SouthWest,
	West,
	NorthWest
};

class Map : public GameObject {
public:
	Map(int width, int height, std::vector<int> tiles);
	virtual ~Map();

	int Width() { return width; }
	int Height() { return height; }

	Point2 GetMaxDistanceInDirectionTravelable(Point StartPos, Direction direction);

	Point2 GetTilePosition(Point position);

private:
	int width;
	int height;

	std::vector< std::vector<Tile*> > tiles;

};

#endif