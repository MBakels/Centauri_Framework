#ifndef MAP_H
#define MAP_H

#include "scene.h"
#include "tile.h"
#include "player.h"
#include "textfile.h"

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

class Map : public Scene {
public:
	Map(std::string filepath);
	virtual ~Map();

	virtual void Update();

private:
	int width;
	int height;

	std::vector< std::vector<Tile*> > tiles;

	Player* player;

	Vector2 GetDirection();

	Point2 GetMaxDistanceInDirectionTravelable(Point2 StartPos, Vector2 direction);

};

#endif