#include "map.h"

Map::Map(std::string filepath) {
	// Seed the random number generator
	srand(time(NULL));
	// Setup temp variables
	std::vector<int> tiles;
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
				sscanf(lineoftext.c_str(), "s %d %d", &width, &height);
			}
			// Tiles
			if (lineoftext[0] == 't') {
				for (int i = 2; i < lineoftext.length(); ++i) {
					tiles.push_back(lineoftext[i] - 48);
				}
			}
			// Player
			if (lineoftext[0] == 'p') {
				int xPos, yPos;
				sscanf(lineoftext.c_str(), "p %d %d", &xPos, &yPos);
				player = new Pinguin(xPos, yPos, 3);
				AddChild(player);
			}
			// Enemy
			if (lineoftext[0] == 'e') {
				int xPos, yPos;
				sscanf(lineoftext.c_str(), "e %d %d", &xPos, &yPos);
				Pinguin* enemy = new Pinguin(xPos, yPos, 2);
				enemys.push_back(enemy);
				AddChild(enemy);
			}
		}
		// Close the file
		textfile.Close();
	} else {
		// Print error if the file is not found
		std::cout << "ERROR::File not found: " << filepath << std::endl;
	}

	int tileIndex = 0; // Temp int tileIndex
	// Create grid of tiles
	for (int x = 0; x < width; x++) {
		std::vector<Tile*> tempVec;
		for (int y = 0; y < height; y++) {
			// Create tile and add tile to tempVec
			tempVec.push_back(new Tile(x, y, tiles[tileIndex]));
			AddChild(tempVec.back());
			tileIndex++;
		}
		// Push tempVec into tiles
		this->tiles.push_back(tempVec);
	}

	// Set camera starting position
	GetCamera()->position = Point3(player->position.x, player->position.y, 100);

	// Create the pause menu
	pauseMenu = new PauseMenu();
	AddChild(pauseMenu);
}

Map::~Map() {
	// Remove player
	RemoveChild(player);
	delete player;

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
}

void Map::Update() {
	// Toggle pause menu if the escape key has been pressed
	if (GetInput()->GetKeyDown(KeyCode::GraveAccent)) {
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
	// Check for right mouse press
	if (GetInput()->GetMouseDown(1)) {
		float angle = atan2(GetInput()->GetMouseY(), GetInput()->GetMouseX());
		//Point3 rotation = Point3(0, 0, (PI * 1.5) + angle);
		std::cout << angle << std::endl;
	}

	// Update enemy AI
	EnemyAI();

	// (Temp) Close game
	if (GetInput()->GetKey(KeyCode::EscapeKey)) {
		GetInput()->ExitApplication();
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
	if (tilePos.x >= width || tilePos.x < 0 || tilePos.y >= height || tilePos.y < 0) {
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
		// Check if an enemy is moving
		if (!enemy->IsMoving()) {
			// Get all potential direction enemy can move in
			std::vector<Vector2> directions = GetPotentialMoveDirections(Point2(enemy->x, enemy->y));
			// Pick a random direction from list
			Vector2 randomDirection = directions[rand() % directions.size()];
			// Get the max reachable tile in the direction from above
			Point2 tilePos = GetTilePositionOfMaxReachableTileInDirection(Point2(enemy->x, enemy->y), randomDirection);
			// Move the enemy in to the position
			enemy->MoveTo(tilePos, randomDirection);
		}
	}
}