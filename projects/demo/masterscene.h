#ifndef MASTERSCENE_H
#define MASTERSCENE_H

#include "scene.h"

class MasterScene : public Scene {
public:
	MasterScene();
	virtual ~MasterScene();

	virtual void Update();

private:
	static int activescene;
	static int numberOfScenes;
};

#endif
