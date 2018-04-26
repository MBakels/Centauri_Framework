#ifndef SCENE_H
#define SCENE_H

#include "gameobject.h"
#include "camera.h"

class Scene : public GameObject {
public:
	Scene();
	virtual ~Scene();

	Camera* GetCamera() { return _camera; };

	void UpdateScene(float deltaTime);

private:
	void UpdateGameObject(GameObject* gameObject, float deltaTime);

	Camera* _camera;
};

#endif
