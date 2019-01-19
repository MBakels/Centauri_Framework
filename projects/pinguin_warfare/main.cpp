#include "core.h"

#include "map.h"

int main() {

	Core core;

	Map* map = new Map("maps/test.m");

	while (core.IsRunning()) {
		core.Run(map);
	}

	delete map;

	return 0;
}