#include "core.h"

#include "scene01.h"
#include "scene02.h"
#include "scene03.h"

int main() {

	Core core;

	std::vector<MasterScene*> scenes;
	scenes.push_back(new Scene01());
	scenes.push_back(new Scene02());
	scenes.push_back(new Scene03());
	int s = scenes.size();

	MasterScene* scene = scenes[0];
	int scenecounter = 0;
	while (core.IsRunning()) {
		scenecounter = scene->activescene;
		if (scenecounter > s - 1) { scenecounter = 0; scene->activescene = 0; }
		if (scenecounter < 0) { scenecounter = s - 1; scene->activescene = s - 1; }
		scene = scenes[scenecounter];
		core.Run(scene);
		//core.ShowFrameRate(5);
	}

	for (int i = 0; i < s; i++) {
		delete scenes[i];
		scenes[i] = NULL;
	}
	scenes.clear();

	return 0;
}