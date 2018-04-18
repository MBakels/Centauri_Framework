#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"
#include "gameobject.h"
#include "playership.h"
#include "laser.h"
#include "enemyship.h"

class GameScene : public Scene {
public:
	GameScene();
	virtual ~GameScene();

	virtual void update(float deltaTime);

private:
	PlayerShip* player;

	std::vector<Laser*> lasers;
	std::vector<EnemyShip*> enemys;

	float time;

	void spawnEnemy(float deltaTime);
	void checkCollisions();
	float distance(Point pointOne, Point PointTwo);
};

#endif