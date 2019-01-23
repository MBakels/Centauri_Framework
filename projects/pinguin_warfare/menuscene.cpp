#include "menuscene.h"
#include "scenemanager.h"

MenuScene::MenuScene() {
	// Start game button
	startButton = new Button(Point2(SWIDTH / 2, 200, 10), "assets/StartGameButton.png");
	AddChild(startButton);

	// Enter map builder button
	mapBuilderButton = new Button(Point2(SWIDTH / 2, 400, 10), "assets/MapMakerButton.png");
	AddChild(mapBuilderButton);

	// Quit game button
	quitButton = new Button(Point2(SWIDTH / 2, 600, 10), "assets/QuitGameButton.png");
	AddChild(quitButton);
}

MenuScene::~MenuScene() {
	RemoveChild(startButton);
	delete startButton;
	RemoveChild(mapBuilderButton);
	delete mapBuilderButton;
	RemoveChild(quitButton);
	delete quitButton;
}

void MenuScene::Update() {
	if (GetInput()->GetKey(KeyCode::EscapeKey)) {
		GetInput()->ExitApplication();
	}
	// Chack button input
	if (startButton->CheckPressed(Point2(GetInput()->GetMouseX(), GetInput()->GetMouseY()))) {
		SceneMaganger::LoadScene(1);
	}
	if (mapBuilderButton->CheckPressed(Point2(GetInput()->GetMouseX(), GetInput()->GetMouseY()))) {
		std::cout << "Map builder" << std::endl;
		//SceneMaganger::LoadScene(1);
	}
	if (quitButton->CheckPressed(Point2(GetInput()->GetMouseX(), GetInput()->GetMouseY()))) {
		GetInput()->ExitApplication();
	}
}