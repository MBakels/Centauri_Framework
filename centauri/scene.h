#ifndef SCENE_H
#define SCENE_H

#include "gameobject.h"
#include "camera.h"

class Scene : public GameObject {
public:
	Scene();
	virtual ~Scene();

	Camera* camera() { return _camera; };

	void updateScene(float deltaTime);

private:
	void updateGameObject(GameObject* gameObject, float deltaTime);

	Camera* _camera;
};

#endif
