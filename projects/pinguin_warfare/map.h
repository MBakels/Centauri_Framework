#ifndef MAP_H
#define MAP_H

#include "scene.h"
#include "tile.h"
#include "pinguin.h"
#include "textfile.h"
#include "pausemenu.h"

class Map : public Scene {
public:
	// Constructor of the Map class
	Map(std::string filepath);
	// Destructor of the Map class
	virtual ~Map();

	// Updates the Map Scene
	void Update();

private:
	// Size of the map in number of tiles
	int width;
	int height;

	// A 2D vector for the tiles
	std::vector< std::vector<Tile*> > tiles;
	// A list with the enemys
	std::vector<Pinguin*> enemys;

	// The player
	Pinguin* player;

	//The pause menu
	PauseMenu* pauseMenu;

	// Get the direction of a mouse click
	Vector2 GetDirection();

	// Get the max reachable tile in a given direction, returns "Vector(-1, -1)" if it fails to get a tilePos
	Point2 GetTilePositionOfMaxReachableTileInDirection(Point2 startPos, Vector2 direction);

	// Checks if a tile is in the map bounds
	bool IsTileInBounds(Point2 tilePos);

	// Gets all the available tiles around a given tile
	std::vector<Vector2> GetPotentialMoveDirections(Point2 tilePos);

	// Updates the enemys AI
	void EnemyAI();

};

#endif