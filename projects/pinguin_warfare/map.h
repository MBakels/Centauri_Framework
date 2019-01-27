#ifndef MAP_H
#define MAP_H

#include "scene.h"
#include "tile.h"
#include "pinguin.h"
#include "textfile.h"
#include "pausemenu.h"
#include "snowball.h"

// A struct to hold all map data
struct MapData {
	std::string mapName; // Name of the map
	Point2 mapSize; // Size of the map
	std::vector<int> tiles; // A vector that contains all tiles types
	Point2 playerPosition; // The player position
	std::vector<Point2> enemyPositions; // A vector with all the enemy positions
};

class Map : public Scene {
public:
	// Constructor of the Map class
	Map(std::string mapName);
	// Destructor of the Map class
	virtual ~Map();

	// Updates the Map Scene
	void Update();

	// Load a map and puts its data in the maps vector
	static void LoadMap(std::string filepath);

	// Holds all map data
	static std::map<std::string, MapData*> maps;

private:
	// Map data in struct
	MapData* data;

	// A 2D vector for the tiles
	std::vector< std::vector<Tile*> > tiles;
	// A vector with the enemys
	std::vector<Pinguin*> enemys;
	// A vector with snowballs
	std::vector<SnowBall*> snowBalls;

	// A vector with all solid tiles
	std::vector<Tile*> solids;

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

	// Check for collisions with snowballs
	void SnowBallCollisionCheck();

};

#endif