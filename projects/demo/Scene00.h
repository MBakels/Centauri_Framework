#ifndef SCENE00_H
#define SCENE00_H

#include "scene.h"
#include "gameobject.h"

class Scene00 : public Scene {
public:
	Scene00();
	virtual ~Scene00();

	virtual void Update(float deltaTime);

private:
	Sprite* wood;
	Sprite* pencils;
	Sprite* kingkong;
	GameObject* woodObj;
	GameObject* pencilsObj;
	GameObject* kingkongObj;
};

#endif
