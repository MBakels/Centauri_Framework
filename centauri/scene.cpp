#include "scene.h"

Scene::Scene() {
	_camera = new Camera();
}

Scene::~Scene() {
	delete _camera;
}

void Scene::UpdateScene(float deltaTime) {
	this->UpdateGameObject(this, deltaTime);
}

void Scene::UpdateGameObject(GameObject* gameObject, float deltaTime) {
	gameObject->Update(deltaTime); // Update self

	// Update children
	std::vector<GameObject*> children = gameObject->GetChildren();
	std::vector<GameObject*>::iterator child;
	for (child = children.begin(); child != children.end(); child++) {
		this->UpdateGameObject(*child, deltaTime);
	}
}