#include "scene.h"

Scene::Scene() {
	_camera = new Camera();
}

Scene::~Scene() {
	delete _camera;
}

void Scene::updateScene(float deltaTime) {
	this->updateGameObject(this, deltaTime);
}

void Scene::updateGameObject(GameObject* gameObject, float deltaTime) {
	gameObject->update(deltaTime); // Update self

	// Update children
	std::vector<GameObject*> children = gameObject->children();
	std::vector<GameObject*>::iterator child;
	for (child = children.begin(); child != children.end(); child++) {
		this->updateGameObject(*child, deltaTime);
	}
}