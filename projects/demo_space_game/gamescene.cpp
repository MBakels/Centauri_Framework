#include <fstream>
#include <sstream>
#include "gamescene.h"

GameScene::GameScene() : Scene() {
	std::srand(std::time(nullptr));

	player = new PlayerShip();
	AddChild(player);

	time = 0;
}

GameScene::~GameScene() {
	delete player;

	std::vector<Laser*>::iterator lasersIt = lasers.begin();
	while (lasersIt != lasers.end()) {
		RemoveChild((*lasersIt));
		delete (*lasersIt);
		lasersIt++;
	}
	lasers.clear();

	std::vector<EnemyShip*>::iterator enemysIt = enemys.begin();
	while (enemysIt != enemys.end()) {
		RemoveChild((*enemysIt));
		delete (*enemysIt);
		enemysIt++;
	}
	enemys.clear();
}

void GameScene::Update(float deltaTime) {
	// Quit game
	if (GetInput()->GetKey(KeyCode::EscapeKey)) {
		GetInput()->ExitApplication();
	}

	// Shoot laser on space bar or mouse klik
	if (GetInput()->GetKeyDown(KeyCode::Space) || GetInput()->GetMouseDown(0)) {
		lasers.push_back(new Laser(player->position));
		AddChild(lasers.back());
	}

	// Spawn enemys
	SpawnEnemy(deltaTime);

	// Check Collisions
	CheckCollisions();
}

// Enemy spawner
void GameScene::SpawnEnemy(float deltaTime) {
	time += deltaTime;
	if (time >+1) {
		Point2 randomSpawn = Point2(SWIDTH, (((float)std::rand()) / ((float)(RAND_MAX / SHEIGHT))));
		enemys.push_back(new EnemyShip(randomSpawn));
		AddChild(enemys.back());
		time = 0;
	}
}

void GameScene::CheckCollisions() {
	// End game if enemy gets behind player
	for (EnemyShip* enemy : enemys) {
		if (enemy->position.x < 0) {
			//input()->exitApplication();
		}
	}

	// Remove laser if out of screen
	std::vector<Laser*>::iterator lasersIt = lasers.begin();
	while (lasersIt != lasers.end()) {
		if ((*lasersIt)->position.x > SWIDTH) {
			RemoveChild((*lasersIt));
			delete (*lasersIt);
			lasersIt = lasers.erase(lasersIt);
		} else {
			lasersIt++;
		}
	}

	// Check collision between laser and enemy
	for (Laser* laser : lasers) {
		std::vector<EnemyShip*>::iterator enemysIt = enemys.begin();
		while (enemysIt != enemys.end()) {
			//if (distance((*enemysIt)->position, laser->position) <= 30) {
			if (Point::Distance((*enemysIt)->position, laser->position) <= 30) {
				RemoveChild((*enemysIt));
				delete (*enemysIt);
				enemysIt = enemys.erase(enemysIt);
			} else {
				enemysIt++;
			}
		}
	}
}
