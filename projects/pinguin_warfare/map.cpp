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
		GetDirection();
		//GetMaxDistanceInDirectionTravelable(Point2(GetInput()->GetMouseX(), GetInput()->GetMouseY()), Direction::North);
	}
}

Vector2 Map::GetDirection() {
	double mouseX = GetInput()->GetMouseX();
	double mouseY = GetInput()->GetMouseY();
	Vector2 playerPos = player->position + position;

	double angle = atan2(mouseX - playerPos.x, playerPos.y - mouseY);
	if (angle < 0.0) angle += TWO_PI;
	angle *= 180 / PI;
	std::cout << angle << std::endl;
	return Vector2(0, 0);
}

Point2 Map::GetMaxDistanceInDirectionTravelable(Point StartPos, Direction direction) {
	Point2 tilePos = GetTilePosition(StartPos);
	// If GetTilePosition returns (-1, -1) return fallback to avoid crash
	if (tilePos == Point(-1, -1)) return tilePos;
	Vector2 moveDirection;
	switch (direction) {
		case Direction::North:
			moveDirection = Vector2(0, -1);
			break;
		case Direction::NorthEast:
			moveDirection = Vector2(1, -1);
			break;
		case Direction::East:
			moveDirection = Vector2(1, 0);
			break;
		case Direction::SouthEast:
			moveDirection = Vector2(1, 1);
			break;
		case Direction::South:
			moveDirection = Vector2(0, 1);
			break;
		case Direction::SouthWest:
			moveDirection = Vector2(-1, 1);
			break;
		case Direction::West:
			moveDirection = Vector2(1, 0);
			break;
		case Direction::NorthWest:
			moveDirection = Vector2(-1, -1);
			break;
	}

	do {
		tilePos += moveDirection;
		if (tiles[tilePos.x][tilePos.y]->tileBehaviour == TileBehaviour::SlowDown) {
			tiles[tilePos.x][tilePos.y]->GetSprite()->color.a = 130;
			return tiles[tilePos.x][tilePos.y]->position;
		}
		if (tiles[tilePos.x + moveDirection.x][tilePos.y + moveDirection.y]->tileBehaviour == TileBehaviour::Solid) {
			tiles[tilePos.x][tilePos.y]->GetSprite()->color.a = 130;
			return tiles[tilePos.x][tilePos.y]->position;
		}
	} while (tilePos.x < width && tilePos.y < height);
}

Point2 Map::GetTilePosition(Point position) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Tile* tile = tiles[x][y];
			Point2 tilePos = tile->position;

			int halfwidth = 32;
			int halfheight = 32;
			int left = tilePos.x - halfwidth;
			int right = tilePos.x + halfwidth;
			int top = tilePos.y - halfheight;
			int bottom = tilePos.y + halfheight;

			int checkPosX = position.x - this->position.x;
			int checkPosY = position.y - this->position.y;

			if (checkPosX > left && checkPosX < right && checkPosY > top && checkPosY < bottom) {
				return Point2(tile->x, tile->y);
			}
		}
	}
	// fallback if no tile match found
	return Point(-1, -1);
}
