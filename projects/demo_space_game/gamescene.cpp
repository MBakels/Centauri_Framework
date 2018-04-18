#include <fstream>
#include <sstream>
#include "gamescene.h"

GameScene::GameScene() : Scene() {
	std::srand(std::time(nullptr));

	player = new PlayerShip();
	addChild(player);

	time = 0;
}

GameScene::~GameScene() {
	delete player;

	std::vector<Laser*>::iterator lasersIt = lasers.begin();
	while (lasersIt != lasers.end()) {
		removeChild((*lasersIt));
		delete (*lasersIt);
		lasersIt++;
	}
	lasers.clear();

	std::vector<EnemyShip*>::iterator enemysIt = enemys.begin();
	while (enemysIt != enemys.end()) {
		removeChild((*enemysIt));
		delete (*enemysIt);
		enemysIt++;
	}
	enemys.clear();
}

void GameScene::update(float deltaTime) {
	// Quit game
	if (input()->getKey(KeyCode::EscapeKey)) {
		input()->exitApplication();
	}

	// Shoot laser on space bar or mouse klik
	if (input()->getKeyDown(KeyCode::Space) || input()->getMouseDown(0)) {
		lasers.push_back(new Laser(player->position));
		addChild(lasers.back());
	}

	// Spawn enemys
	spawnEnemy(deltaTime);

	// Check Collisions
	checkCollisions();
}

// Enemy spawner
void GameScene::spawnEnemy(float deltaTime) {
	time += deltaTime;
	if (time >+1) {
		Point2 randomSpawn = Point2(SWIDTH, (((float)std::rand()) / ((float)(RAND_MAX / SHEIGHT))));
		enemys.push_back(new EnemyShip(randomSpawn));
		addChild(enemys.back());
		time = 0;
	}
}

void GameScene::checkCollisions() {
	// End game if enemy gets behind player
	for each (EnemyShip* enemy in enemys) {
		if (enemy->position.x < 0) {
			input()->exitApplication();
		}
	}

	// Remove laser if out of screen
	std::vector<Laser*>::iterator lasersIt = lasers.begin();
	while (lasersIt != lasers.end()) {
		if ((*lasersIt)->position.x > SWIDTH) {
			removeChild((*lasersIt));
			delete (*lasersIt);
			lasersIt = lasers.erase(lasersIt);
		} else {
			lasersIt++;
		}
	}

	// Check collision between laser and enemy
	for each (Laser* laser in lasers) {
		std::vector<EnemyShip*>::iterator enemysIt = enemys.begin();
		while (enemysIt != enemys.end()) {
			if (distance((*enemysIt)->position, laser->position) <= 30) {
				removeChild((*enemysIt));
				delete (*enemysIt);
				enemysIt = enemys.erase(enemysIt);
			} else {
				enemysIt++;
			}
		}
	}
}

float GameScene::distance(Point pointOne, Point pointTwo) {
	float distanceX = (pointTwo.x - pointOne.x) * (pointTwo.x - pointOne.x);
	float distanceY = (pointTwo.y - pointOne.y) * (pointTwo.y - pointOne.y);
	return sqrt(distanceX + distanceY);
}