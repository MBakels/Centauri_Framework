#ifndef SCENE_H
#define SCENE_H

#include "gameobject.h"

class Scene : public GameObject {
public:
	Scene();
	virtual ~Scene();

	// Gets called after SceneManager loads the scene
	virtual void SceneLoaded() {};

	Camera* GetCamera() { return _camera; };

	void UpdateScene();

private:
	void UpdateGameObject(GameObject* gameObject);

	Camera* _camera;
};

#endif
