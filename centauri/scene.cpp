#include "scene.h"

Scene::Scene() {
	_camera = new Camera();
}

Scene::~Scene() {
	delete _camera;
}

void Scene::UpdateScene(float deltaTime) {
	// Update camera in the scene
	_camera->UpdateCamera();

	// Update all game objects in scene
	this->UpdateGameObject(this, deltaTime);
}

void Scene::UpdateGameObject(GameObject* gameObject, float deltaTime) {
	gameObject->Update(deltaTime); // Update self

	// Update children
	std::vector<GameObject*> children = gameObject->Children();
	std::vector<GameObject*>::iterator child;
	for (child = children.begin(); child != children.end(); child++) {
		this->UpdateGameObject(*child, deltaTime);
	}
}