#ifndef MAPMAKER_H
#define MAPMAKER_H

#include "scene.h"
#include "map.h"
#include "tile.h"

class MapMaker : public Scene {
public:
	// Constructor of the MapMaker class
	MapMaker(std::string mapName, Point2 mapSize = Point2(0, 0));
	// Destructor of the MapMaker class
	virtual ~MapMaker();

	// Updates the map maker scene
	void Update();

private:
	// Text explaining to map maker
	GameObject* explanationText;

	// Map data in struct
	MapData* data;

	// A 2D vector for the tiles
	std::vector< std::vector<Tile*> > tiles;
	// A vector with the enemy positions
	//std::vector<Vector2> enemyPositions;
	// Player position
	//Vector2 playerPosition;
};

#endif
