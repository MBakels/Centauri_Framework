#include "core.h"

#include "Scene00.h"

int main() {

	Core core;

	Scene00* scene00 = new Scene00();

	while (core.isRunning()) {
		core.run(scene00);
		//core.showFrameRate(5);
	}

	delete scene00;

	return 0;
}