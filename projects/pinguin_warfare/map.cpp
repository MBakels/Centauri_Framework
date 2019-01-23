#include "map.h"

Map::Map(std::string filepath) : Scene() {
	srand(time(NULL));
	std::vector<int> tiles;
	TextFile textfile;

	// Try to open the file
	if (textfile.Open(filepath.c_str())) {
		// Start reading the file
		textfile.StartReading();
		while (!textfile.EndOfFile()) {
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

	position = Vector3(SWIDTH / 2 - width * 32 + 32, SHEIGHT / 2 - height * 32 + 32, 0);
	int tileIndex = 0;
	for (int x = 0; x < width; x++) {
		std::vector<Tile*> tempVec;
		for (int y = 0; y < height; y++) {
			tempVec.push_back(new Tile(x, y, tiles[tileIndex]));
			AddChild(tempVec.back());
			tileIndex++;
		}
		this->tiles.push_back(tempVec);
	}
}

Map::~Map() {
	RemoveChild(player);
	delete player;

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

	std::vector<Pinguin*>::iterator enemysIt;
	for (enemysIt = enemys.begin(); enemysIt != enemys.end(); enemysIt++) {
		RemoveChild((*enemysIt));
		delete (*enemysIt);
	}
	enemys.clear();
}

void Map::Update() {
	if (GetInput()->GetKeyDown(KeyCode::GraveAccent)) {
		if (Time::timeScale == 1) {
			Time::timeScale = 0;
		} else {
			Time::timeScale = 1;
		}
	}
	if (GetInput()->GetKey(KeyCode::EscapeKey)) {
		GetInput()->ExitApplication();
	}
	if (GetInput()->GetMouseDown(0) && !player->IsMoving()) {
		Vector2 direction = GetDirection();
		Point2 tilePos = GetTilePositionOfMaxReachableTileInDirection(Point2(player->x, player->y), direction);
		if (tilePos != Vector2(-1, -1)) player->MoveTo(tilePos, direction);
	}
	EnemyAI();
}

Vector2 Map::GetDirection() {
	double mouseX = GetInput()->GetMouseX();
	double mouseY = GetInput()->GetMouseY();
	Vector2 playerPos = player->position + position;

	float angle = atan2(mouseX - playerPos.x, playerPos.y - mouseY);
	if (angle < 0.0) angle += TWO_PI;
	angle *= 180 / PI;

	if (angle > 22.5f && angle <= 67.5f) {
		// NorthEast
		return Vector2(1, -1);
	} else if (angle >= 67.5f && angle <= 112.5f) {
		// East
		return Vector2(1, 0);
	} else if (angle >= 112.5f && angle <= 157.5f) {
		// SouthEast
		return Vector2(1, 1);
	} else if (angle >= 157.5f && angle <= 202.5f) {
		// South
		return Vector2(0, 1);
	} else if (angle >= 202.5f && angle <= 247.5f) {
		// SouthWest
		return Vector2(-1, 1);
	} else if (angle >= 247.5f && angle <= 292.5f) {
		// West
		return Vector2(-1, 0);
	} else if (angle >= 292.5f && angle <= 337.5f) {
		// NorthWest
		return Vector2(-1, -1);
	} else {
		// North
		return Vector2(0, -1);
	}
}

Point2 Map::GetTilePositionOfMaxReachableTileInDirection(Point2 StartPos, Vector2 direction) {
	do {
		StartPos += direction;
		if (!IsTileInBounds(StartPos)) return Vector2(-1, -1);
		Tile* tile = tiles[StartPos.x][StartPos.y];
		if (tile->tileBehaviour == TileBehaviour::SlowDown) {
			//tile->GetSprite()->color.a = 130;
			return Point2(tile->x, tile->y);
		}
		if (tiles[StartPos.x + direction.x][StartPos.y + direction.y]->tileBehaviour == TileBehaviour::Solid) {
			//tile->GetSprite()->color.a = 130;
			return Point2(tile->x, tile->y);
		}

	} while (true);
}

bool Map::IsTileInBounds(Point2 tilePos) {
	if (tilePos.x >= width || tilePos.x < 0 || tilePos.y >= height || tilePos.y < 0) {
		return false;
	}
	return true;
}

std::vector<Vector2> Map::GetPotentialMoveDirections(Point2 tilePos) {
	std::vector<Vector2> potentialDirections;
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			if (x == 0 && y == 0) continue;
			if (IsTileInBounds(Point2(tilePos.x + x, tilePos.y + y))) {
				potentialDirections.push_back(Vector2(x, y));
			}
		}
	}
	return potentialDirections;
}

void Map::EnemyAI() {
	for each (Pinguin* enemy in enemys) {
		if (!enemy->IsMoving()) {
			std::vector<Vector2> directions = GetPotentialMoveDirections(Point2(enemy->x, enemy->y));
			Vector2 randomDirection = directions[rand() % directions.size()];
			Point2 tilePos = GetTilePositionOfMaxReachableTileInDirection(Point2(enemy->x, enemy->y), randomDirection);
			enemy->MoveTo(tilePos, randomDirection);
		}
	}
}