#ifndef MASTERSCENE_H
#define MASTERSCENE_H

#include "scene.h"

class MasterScene : public Scene {
public:
	MasterScene();
	virtual ~MasterScene();

	virtual void Update();

	static int activescene;
};

#endif
