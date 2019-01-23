#include "menuscene.h"
#include "scenemanager.h"

MenuScene::MenuScene() {
	startButton = new Button(Point2(200, 100, 10), "button", "assets/white.png", BLACK);
	startButton->AddButtonText("X", 50);
	AddChild(startButton);
}

MenuScene::~MenuScene() {
	RemoveChild(startButton);
	delete startButton;
}

void MenuScene::Update() {
	if (GetInput()->GetKey(KeyCode::EscapeKey)) {
		GetInput()->ExitApplication();
	}
	if (startButton->CheckPressed(Point2(GetInput()->GetMouseX(), GetInput()->GetMouseY()))) {
		SceneMaganger::LoadScene(1);
	}
}