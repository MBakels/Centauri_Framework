#include "core.h"

#include "Scene00.h"

int main() {

	Core core;

	Scene00* scene00 = new Scene00();

	while (core.IsRunning()) {
		core.Run(scene00);
		//core.ShowFrameRate(5);
	}
	return 0;
}