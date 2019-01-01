#ifndef SCENE03_H
#define SCENE03_H

#include "masterscene.h"

class Scene03 : public MasterScene {
public:
	Scene03();
	virtual ~Scene03();

	virtual void Update();

private:
	GameObject* circle;
	GameObject* square;
};

#endif
