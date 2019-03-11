#include "mapmaker.h"

MapMaker::MapMaker(std::string mapName, Point2 mapSize) {
	// Check if a map with the given name exists
	std::map<std::string, MapData*>::iterator mapsIt = Map::maps.find(mapName);
	if (mapsIt != Map::maps.end()) {
		// Get data for the given map
		data = mapsIt->second;
	} else {
		data = new MapData();
		data->mapName = mapName;
		data->mapSize = mapSize;
	}

	int tileIndex = 0; // Temp int tileIndex
	// Create grid of tiles
	for (int x = 0; x < data->mapSize.x; x++) {
		std::vector<Tile*> tempVec;
		for (int y = 0; y < data->mapSize.y; y++) {
			// Create tile and add tile to tempVec
			Tile* tile = new Tile(x, y, data->tiles[tileIndex]);
			AddChild(tile);
			tempVec.push_back(tile);
			tileIndex++;
		}
		// Push tempVec into tiles
		this->tiles.push_back(tempVec);
	}
	
}

MapMaker::~MapMaker() {

}

void MapMaker::Update() {

}