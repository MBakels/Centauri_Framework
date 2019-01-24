#include "scene.h"

Scene::Scene() {
	_camera = new Camera();
}

Scene::~Scene() {
	delete _camera;
}

void Scene::UpdateScene() {
	// Update camera in the scene
	_camera->UpdateCamera();

	// Update all game objects in scene
	this->UpdateGameObject(this);
}

void Scene::UpdateGameObject(GameObject* gameObject) {
	if (!gameObject->isActive) return;
	gameObject->Update(); // Update self

	// Update children
	std::vector<GameObject*> children = gameObject->Children();
	std::vector<GameObject*>::iterator child;
	for (child = children.begin(); child != children.end(); child++) {
		this->UpdateGameObject(*child);
	}
}