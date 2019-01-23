#ifndef MAP_H
#define MAP_H

#include "scene.h"
#include "tile.h"
#include "pinguin.h"
#include "textfile.h"

class Map : public Scene {
public:
	Map(std::string filepath);
	virtual ~Map();

	void testlog() {
		std::cout << "working" << std::endl;
	}

	void Update();

private:
	int width;
	int height;

	std::vector< std::vector<Tile*> > tiles;
	std::vector<Pinguin*> enemys;

	Pinguin* player;

	Vector2 GetDirection();

	Point2 GetTilePositionOfMaxReachableTileInDirection(Point2 StartPos, Vector2 direction);

	bool IsTileInBounds(Point2 tilePos);

	std::vector<Vector2> GetPotentialMoveDirections(Point2 tilePos);

	void EnemyAI();

};

#endif