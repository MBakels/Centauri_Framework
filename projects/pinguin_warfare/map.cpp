#include <stdlib.h>

#include "map.h"
#include "scenemanager.h"

std::map<std::string, MapData*> Map::maps;

Map::Map(std::string mapName) {
	// Seed the random number generator
	srand(time(NULL));

	// Setup the variables
	player = NULL;

	// Get data for this map
	data = maps[mapName];

	int tileIndex = 0; // Temp int tileIndex
	// Create grid of tiles
	for (int x = 0; x < data->mapSize.x; x++) {
		std::vector<Tile*> tempVec;
		for (int y = 0; y < data->mapSize.y; y++) {
			// Create tile and add tile to tempVec
			tempVec.push_back(new Tile(x, y, data->tiles[tileIndex]));
			AddChild(tempVec.back());
			tileIndex++;
		}
		// Push tempVec into tiles
		this->tiles.push_back(tempVec);
	}

	// Create the player
	player = new Pinguin(data->playerPosition.x, data->playerPosition.y, 4, 1);
	AddChild(player);

	// Set camera starting position
	GetCamera()->position = Point3(player->position.x, player->position.y, 100);

	// Create the enemys
	for each (Point2 enemyPos in data->enemyPositions) {
		Pinguin* enemy = new Pinguin(enemyPos.x, enemyPos.y, 3, 2);
		enemys.push_back(enemy);
		AddChild(enemy);
	}

	// Create the pause menu
	pauseMenu = new PauseMenu();
	AddChild(pauseMenu);
}

Map::~Map() {
	// Remove player
	RemoveChild(player);
	delete player;

	// Remove pause menu
	RemoveChild(pauseMenu);
	delete pauseMenu;

	// Remove tiles
	std::vector<std::vector<Tile*>>::iterator tilesRowIt;
	std::vector<Tile*>::iterator tilesColIt;
	for (tilesRowIt = tiles.begin(); tilesRowIt != tiles.end(); tilesRowIt++) {
		for (tilesColIt = tilesRowIt->begin(); tilesColIt != tilesRowIt->end(); tilesColIt++) {
			RemoveChild((*tilesColIt));
			delete (*tilesColIt);
		}
		tilesRowIt->clear();
	}
	tiles.clear();

	// Remove enemys
	std::vector<Pinguin*>::iterator enemysIt;
	for (enemysIt = enemys.begin(); enemysIt != enemys.end(); enemysIt++) {
		RemoveChild((*enemysIt));
		delete (*enemysIt);
	}
	enemys.clear();

	// Remove snowballs
	std::vector<SnowBall*>::iterator snowBallsIt;
	for (snowBallsIt = snowBalls.begin(); snowBallsIt != snowBalls.end(); snowBallsIt++) {
		RemoveChild((*snowBallsIt));
		delete (*snowBallsIt);
	}
	snowBalls.clear();
}

void Map::LoadMap(std::string filepath) {
	// Create data struct
	MapData* mapData = new MapData();

	// file name
	char fname[_MAX_FNAME];
	// Geting the map name
	errno_t err = _splitpath_s(filepath.c_str(), NULL, 0, NULL, 0, fname, _MAX_FNAME, NULL, 0);
	// Assign the file name as the map name
	mapData->mapName = fname;
	// Log the error if we get one
	if (err != 0) {
		std::cout << "Error splitting the path. Error code: " << err << std::endl;
	}

	// Setup textfile
	TextFile textfile;

	// Try to open the file
	if (textfile.Open(filepath.c_str())) {
		// Start reading the file
		textfile.StartReading();
		// Keep reading until we reach the end of the file
		while (!textfile.EndOfFile()) {
			// Read a line
			std::string lineoftext = textfile.ReadLine();
			// Map size
			if (lineoftext[0] == 's') {
				int width, height;
				sscanf(lineoftext.c_str(), "s %d %d", &width, &height);
				mapData->mapSize = Point2(width, height);
			}
			// Tiles
			if (lineoftext[0] == 't') {
				for (int i = 2; i < lineoftext.length(); ++i) {
					mapData->tiles.push_back(lineoftext[i] - 48);
				}
			}
			// Player
			if (lineoftext[0] == 'p') {
				int xPos, yPos;
				sscanf(lineoftext.c_str(), "p %d %d", &xPos, &yPos);
				mapData->playerPosition = Point2(xPos, yPos);
			}
			// Enemy
			if (lineoftext[0] == 'e') {
				int xPos, yPos;
				sscanf(lineoftext.c_str(), "e %d %d", &xPos, &yPos);
				mapData->enemyPositions.push_back(Point2(xPos, yPos));
			}
		}
		// Close the file
		textfile.Close();
	} else {
		// Print error if the file is not found
		std::cout << "ERROR::File not found: " << filepath << std::endl;
	}

	// Add data to vector
	Map::maps[mapData->mapName] = mapData;
}

void Map::Update() {
	// Toggle pause menu if the escape key has been pressed
	if (GetInput()->GetKeyDown(KeyCode::EscapeKey)) {
		pauseMenu->Toggle();
	}
	// Check the state of the pause menu
	if (pauseMenu->isActive) {
		// Update the pause menu if the pause menu is active
		pauseMenu->Update(GetCamera()->position);
		// Return to stop updating the rest of the scene
		return;
	}

	// Camera follows the player
	GetCamera()->position = Vector3(player->position.x, player->position.y, 100);

	// Player movement
	// Check for left mouse press and check if the player is not moving
	if (GetInput()->GetMouseDown(0) && !player->IsMoving()) {
		// Get the direction of the mouse click
		Vector2 direction = GetDirection();
		// Get the max reachable tile in the direction from above
		Point2 tilePos = GetTilePositionOfMaxReachableTileInDirection(Point2(player->x, player->y), direction);
		// Check if tilePos returned a valid point, if point is valid move the player to position
		if (tilePos != Point2(-1, -1)) player->MoveTo(tilePos, direction);
	}

	// Player snowball throwing
	// Check for right mouse press and check if the player can throw a snowball
	if (GetInput()->GetMouseDown(1) && player->CanThrow()) {
		// Let the player know a snowball has been thrown
		player->SnowBallThrown();
		// Get mouse position in world space
		Vector2 mousePosWorld = Vector2(GetInput()->GetMouseX() + GetCamera()->position.x - SWIDTH / 2, GetInput()->GetMouseY() + GetCamera()->position.y - SHEIGHT / 2);
		// Get the direction by subtracting player pos from mouse world pos
		Vector2 direction = mousePosWorld - Vector2(player->position.x, player->position.y);
		// Normalize the direction vector
		direction.normalize();

		// Create a snowball, add it to the snowballs vector
		snowBalls.push_back(new SnowBall(player->position, direction, true));
		// Add snowball to scene
		AddChild(snowBalls.back());
	}

	// Update enemy AI
	EnemyAI();

	// Check for snowball collisions
	SnowBallCollisionCheck();

	// Check if the player is alive
	if (!player->IsAlive()) {
		// Load lose menu
		SceneMaganger::LoadScene(3);
	}

	// Check win condition, if all enemy pinguins are dead you win
	if (enemys.empty()) {
		// Load win menu
		SceneMaganger::LoadScene(2);
	}
}

Vector2 Map::GetDirection() {
	// Calculate angle in degrees
	float angle = atan2(GetInput()->GetMouseY() - SHEIGHT / 2, GetInput()->GetMouseX() - SWIDTH / 2);
	if (angle < 0.0) angle += TWO_PI;
	angle *= 180 / PI;

	// Check angle and return direction
	if (angle > 22.5f && angle <= 67.5f) {
		// SouthEast
		return Vector2(1, 1);
	} else if (angle >= 67.5f && angle <= 112.5f) {
		// South
		return Vector2(0, 1);
	} else if (angle >= 112.5f && angle <= 157.5f) {
		// SouthWest
		return Vector2(-1, 1);
	} else if (angle >= 157.5f && angle <= 202.5f) {
		// West
		return Vector2(-1, 0);
	} else if (angle >= 202.5f && angle <= 247.5f) {
		// NorthWest
		return Vector2(-1, -1);
	} else if (angle >= 247.5f && angle <= 292.5f) {
		// North
		return Vector2(0, -1);
	} else if (angle >= 292.5f && angle <= 337.5f) {
		// NorthEast
		return Vector2(1, -1);
	} else {
		// East
		return Vector2(1, 0);
	}
}

Point2 Map::GetTilePositionOfMaxReachableTileInDirection(Point2 startPos, Vector2 direction) {
	// Loop until value is returned
	do {
		startPos += direction;
		// Check if startPos is in map grid bounds
		if (!IsTileInBounds(startPos)) return Vector2(-1, -1);
		// Get the tile
		Tile* tile = tiles[startPos.x][startPos.y];
		// Check if the tileBehaviour is SlowDown and if true return tile position in grid
		if (tile->tileBehaviour == TileBehaviour::SlowDown) {
			return Point2(tile->x, tile->y);
		}
		// Check if the tileBehaviour of the next tile is Solid and if true return its position in grid
		if (tiles[startPos.x + direction.x][startPos.y + direction.y]->tileBehaviour == TileBehaviour::Solid) {
			return Point2(tile->x, tile->y);
		}
	} while (true);
}

bool Map::IsTileInBounds(Point2 tilePos) {
	// Check if tile is in map grid bounds
	if (tilePos.x >= data->mapSize.x || tilePos.x < 0 || tilePos.y >= data->mapSize.y || tilePos.y < 0) {
		return false;
	}
	return true;
}

std::vector<Vector2> Map::GetPotentialMoveDirections(Point2 tilePos) {
	// A vector to hold to potential move direction
	std::vector<Vector2> potentialDirections;
	// Loop through positions around a tilePos
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			// continue if x and y are 0, this is the given tilePos
			if (x == 0 && y == 0) continue;
			// Check if the tile is in bounds on the map grid
			if (IsTileInBounds(Point2(tilePos.x + x, tilePos.y + y))) {
				// Add the direction to the potentialDirections vector
				potentialDirections.push_back(Vector2(x, y));
			}
		}
	}
	// Return results
	return potentialDirections;
}

void Map::EnemyAI() {
	// Loop through all enemys
	for each (Pinguin* enemy in enemys) {
		// Enemy movement
		// Check if an enemy is moving
		if (!enemy->IsMoving()) {
			// Get all potential directions the enemy can move in
			std::vector<Vector2> directions = GetPotentialMoveDirections(Point2(enemy->x, enemy->y));
			// Pick a random direction from list
			Vector2 randomDirection = directions[rand() % directions.size()];
			// Get the max reachable tile in the direction from above
			Point2 tilePos = GetTilePositionOfMaxReachableTileInDirection(Point2(enemy->x, enemy->y), randomDirection);
			// Move the enemy to the position
			enemy->MoveTo(tilePos, randomDirection);
		}

		// Enemy snowball throwing
		// Check if enemy can throw a snowball
		if (enemy->CanThrow()) {
			// Let the enemy know a snowball has been thrown
			enemy->SnowBallThrown();
			// Get the direction by subtracting enemy pos from player pos
			Vector2 direction = Vector2(player->position.x, player->position.y) - Vector2(enemy->position.x, enemy->position.y);
			// Normalize the direction vector
			direction.normalize();
			// Create a snowball, add it to the snowballs vector
			snowBalls.push_back(new SnowBall(enemy->position, direction, false));
			// Add snowball to scene
			AddChild(snowBalls.back());
		}
	}
}

void Map::SnowBallCollisionCheck() {
	// Check for collisions between the player and a snowball
	std::vector<SnowBall*>::iterator snowBallsIt = snowBalls.begin();
	while (snowBallsIt != snowBalls.end()) {
		float distance = Point::Distance((*snowBallsIt)->position, player->position);
		// Check if the snowball is not thrown by the player(player cant hit himself),
		// and check if the distance is greater than the combined sprite sizes.
		// A small amount is subtracted from the player size so that the snowball can get a bit closer
		if (!(*snowBallsIt)->ThrownByPlayer() && distance <= (*snowBallsIt)->GetSprite()->size.x + player->GetSprite()->size.x - 30) {
			player->RemoveLive();
			RemoveChild((*snowBallsIt));
			delete (*snowBallsIt);
			snowBallsIt = snowBalls.erase(snowBallsIt);
		} else {
			snowBallsIt++;
		}
	}

	// Check for collisions between the enemys and a snowball
	std::vector<Pinguin*>::iterator enemysIt = enemys.begin();
	while (enemysIt != enemys.end()) {
		std::vector<SnowBall*>::iterator snowBallsIt = snowBalls.begin();
		while (snowBallsIt != snowBalls.end()) {
			float distance = Point::Distance((*snowBallsIt)->position, (*enemysIt)->position);
			// Check if the snowball is thrown by the player(only the player can hit the enemys),
			// and check if the distance is greater than the combined sprite sizes.
			// A small amount is subtracted from the enemy size so that the snowball can get a bit closer
			if ((*snowBallsIt)->ThrownByPlayer() && distance <= (*snowBallsIt)->GetSprite()->size.x + (*enemysIt)->GetSprite()->size.x - 30) {
				(*enemysIt)->RemoveLive();
				RemoveChild((*snowBallsIt));
				delete (*snowBallsIt);
				snowBallsIt = snowBalls.erase(snowBallsIt);
			} else {
				snowBallsIt++;
			}
		}

		// Check if the enemy is alive, if not remove it
		if (!(*enemysIt)->IsAlive()) {
			RemoveChild((*enemysIt));
			delete (*enemysIt);
			enemysIt = enemys.erase(enemysIt);
		} else {
			enemysIt++;
		}

	}
}
