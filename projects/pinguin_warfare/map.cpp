#include "map.h"

Map::Map(int width, int height, std::vector<int> tiles) : GameObject() {
	this->width = width;
	this->height = height;
	position = Vector3(SWIDTH / 2 - width * 32 + 32, SHEIGHT / 2 - height * 32 + 32, 0);
	int tileIndex = 0;
	for (int x = 0; x < height; x++) {
		std::vector<Tile*> tempVec;
		for (int y = 0; y < width; y++) {
			tempVec.push_back(new Tile(x, y, tiles[tileIndex]));
			AddChild(tempVec.back());
			tileIndex++;
		}
		this->tiles.push_back(tempVec);
	}
}

Map::~Map() {

}

Point2 Map::GetMaxDistanceInDirectionTravelable(Point StartPos, Direction direction) {
	Point2 tilePos = GetTilePosition(StartPos);
	// If GetTilePosition returns (-1, -1) return fallback to avoid crash
	if (tilePos == Point(-1, -1)) tilePos;
	do {
		switch (direction) {
			case Direction::North:
				if (tiles[tilePos.x][tilePos.y - 1]->tileBehaviour == TileBehaviour::Solid) return tiles[tilePos.x][tilePos.y]->position;
				tilePos.y -= 1;
				break;
			case Direction::NorthEast:
				if (tiles[tilePos.x + 1][tilePos.y - 1]->tileBehaviour == TileBehaviour::Solid) return tiles[tilePos.x][tilePos.y]->position;
				tilePos.x += 1;
				tilePos.y -= 1;
				break;
			case Direction::East:
				if (tiles[tilePos.x + 1][tilePos.y]->tileBehaviour == TileBehaviour::Solid) return tiles[tilePos.x][tilePos.y]->position;
				tilePos.x += 1;
				break;
			case Direction::SouthEast:
				if (tiles[tilePos.x + 1][tilePos.y + 1]->tileBehaviour == TileBehaviour::Solid) return tiles[tilePos.x][tilePos.y]->position;
				tilePos.x += 1;
				tilePos.y += 1;
				break;
			case Direction::South:
				if (tiles[tilePos.x][tilePos.y + 1]->tileBehaviour == TileBehaviour::Solid) return tiles[tilePos.x][tilePos.y]->position;
				tilePos.y += 1;
				break;
			case Direction::SouthWest:
				if (tiles[tilePos.x - 1][tilePos.y + 1]->tileBehaviour == TileBehaviour::Solid) return tiles[tilePos.x][tilePos.y]->position;
				tilePos.x -= 1;
				tilePos.y += 1;
				break;
			case Direction::West:
				if (tiles[tilePos.x - 1][tilePos.y]->tileBehaviour == TileBehaviour::Solid) return tiles[tilePos.x][tilePos.y]->position;
				tilePos.x -= 1;
				break;
			case Direction::NorthWest:
				if (tiles[tilePos.x - 1][tilePos.y - 1]->tileBehaviour == TileBehaviour::Solid) return tiles[tilePos.x][tilePos.y]->position;
				tilePos.x -= 1;
				tilePos.y -= 1;
				break;
		}
		if (tiles[tilePos.x][tilePos.y]->tileBehaviour == TileBehaviour::SlowDown) {
			return tiles[tilePos.x][tilePos.y]->position;
		}
	} while (tilePos.x < width && tilePos.y < height);
}

Point2 Map::GetTilePosition(Point position) {
	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {
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
