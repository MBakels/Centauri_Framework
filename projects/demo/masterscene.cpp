#include "masterscene.h"

int MasterScene::activescene = 0;

MasterScene::MasterScene() : Scene() {
	
}

MasterScene::~MasterScene() {

}

void MasterScene::Update() {
	if (GetInput()->GetKey(KeyCode::EscapeKey)) {
		GetInput()->ExitApplication();
	}

	if (GetInput()->GetKeyUp(KeyCode::LeftBracket)) {
		activescene--;
	}
	if (GetInput()->GetKeyUp(KeyCode::RightBracket)) {
		activescene++;
	}
}
