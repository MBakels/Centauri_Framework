#ifndef SCENE_H
#define SCENE_H

#include "gameobject.h"

class Scene : public GameObject {
public:
	Scene();
	virtual ~Scene();

	Camera* GetCamera() { return _camera; };

	void UpdateScene();

private:
	void UpdateGameObject(GameObject* gameObject);

	Camera* _camera;
};

#endif
