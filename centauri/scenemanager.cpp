#include "scenemanager.h"

int SceneMaganger::_currentSceneIndex = 0;
Scene* SceneMaganger::_currentScene = NULL;
std::vector<Scene*> SceneMaganger::_scenes;

SceneMaganger::SceneMaganger() {
	std::cout << "##### SceneManager created #####" << std::endl;
}

SceneMaganger::~SceneMaganger() {
	std::cout << "----- Deleting scenes -----" << std::endl;
	std::vector<Scene*>::iterator scenes_it;
	for (scenes_it = _scenes.begin(); scenes_it != _scenes.end(); ++scenes_it) {
		delete (*scenes_it);
	}
	_scenes.clear();
}

void SceneMaganger::AddScene(Scene* scene) {
	_scenes.push_back(scene);
	if (_currentScene == NULL) {
		_currentScene = scene;
		_currentSceneIndex = 0;
	}
}

void SceneMaganger::LoadScene(int sceneIndex) {
	_currentScene = _scenes[sceneIndex];
	_currentSceneIndex = sceneIndex;
}