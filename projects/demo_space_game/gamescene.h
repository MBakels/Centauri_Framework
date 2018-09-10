#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"
#include "playership.h"
#include "laser.h"
#include "enemyship.h"

class GameScene : public Scene {
public:
	GameScene();
	virtual ~GameScene();

	virtual void Update(float deltaTime);

private:
	PlayerShip* player;

	std::vector<Laser*> lasers;
	std::vector<EnemyShip*> enemys;

	float time;

	void SpawnEnemy(float deltaTime);
	void CheckCollisions();
};

#endif