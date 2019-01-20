#include "map.h"

Map::Map(std::string filepath) : Scene() {
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
				player = new Player(xPos, yPos);
				AddChild(player);
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
}

void Map::Update() {
	if (GetInput()->GetKey(KeyCode::EscapeKey)) {
		GetInput()->ExitApplication();
	}
	if (GetInput()->GetMouseDown(0)) {
		Vector2 direction = GetDirection();
		Point2 tilePos = GetMaxDistanceInDirectionTravelable(Point2(player->x, player->y), direction);
	}
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

Point2 Map::GetMaxDistanceInDirectionTravelable(Point2 StartPos, Vector2 direction) {
	do {
		StartPos += direction;
		if (tiles[StartPos.x][StartPos.y]->tileBehaviour == TileBehaviour::SlowDown) {
			tiles[StartPos.x][StartPos.y]->GetSprite()->color.a = 130;
			return tiles[StartPos.x][StartPos.y]->position;
		}
		if (tiles[StartPos.x + direction.x][StartPos.y + direction.y]->tileBehaviour == TileBehaviour::Solid) {
			tiles[StartPos.x][StartPos.y]->GetSprite()->color.a = 130;
			return tiles[StartPos.x][StartPos.y]->position;
		}
	} while (StartPos.x < width && StartPos.y < height);
}
