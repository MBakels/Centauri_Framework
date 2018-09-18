#ifndef SCENE01_H
#define SCENE01_H

#include "masterscene.h"

class Scene01 : public MasterScene {
public:
	Scene01();
	virtual ~Scene01();

	virtual void Update(float deltaTime);

private:
	GameObject* woodObj;
	GameObject* pencilsObj;
	GameObject* kingkongObj;
};

#endif
