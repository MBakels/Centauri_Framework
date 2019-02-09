#include "masterscene.h"
#include "scenemanager.h"

int MasterScene::activescene = 0;
int MasterScene::numberOfScenes = 0;

MasterScene::MasterScene() : Scene() {
	numberOfScenes = SceneMaganger::ScenesCount();
}

MasterScene::~MasterScene() {

}

void MasterScene::Update() {
	if (GetInput()->GetKey(KeyCode::EscapeKey)) {
		GetInput()->ExitApplication();
	}

	if (GetInput()->GetKeyUp(KeyCode::LeftBracket)) {
		activescene--;
		if (activescene < 0) {
			activescene = numberOfScenes;
		}
		SceneMaganger::LoadScene(activescene);
	}
	if (GetInput()->GetKeyUp(KeyCode::RightBracket)) {
		activescene++;
		if (activescene > numberOfScenes) {
			activescene = 0;
		}
		SceneMaganger::LoadScene(activescene);
	}
}
