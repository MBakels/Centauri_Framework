#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "scene.h"

class SceneMaganger {
public:
	SceneMaganger();
	virtual ~SceneMaganger();

	static void AddScene(Scene* scene);

	static void LoadScene(int sceneIndex);

	static int CurrentSceneIndex() { return _currentSceneIndex; };

	Scene* CurrentScene() { return _currentScene; };

private:
	static std::vector<Scene*> _scenes;

	static int _currentSceneIndex;
	static Scene* _currentScene;

};

#endif
