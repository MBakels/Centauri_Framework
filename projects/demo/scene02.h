#ifndef SCENE02_H
#define SCENE02_H

#include "masterscene.h"

class Scene02 : public MasterScene {
public:
	Scene02();
	virtual ~Scene02();

	virtual void Update(float deltaTime);

private:
	GameObject* circle10;
	GameObject* circle50;
	GameObject* triangle;
};

#endif
