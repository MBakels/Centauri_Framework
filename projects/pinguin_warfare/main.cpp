#include "core.h"

#include "map.h"
#include "menuscene.h"

int main() {

	Core core;

	SceneMaganger::AddScene(new MenuScene());
	SceneMaganger::AddScene(new Map("maps/test.m"));

	//SceneMaganger::LoadScene(1);

	while (core.IsRunning()) {
		core.Run();
	}

	return 0;
}