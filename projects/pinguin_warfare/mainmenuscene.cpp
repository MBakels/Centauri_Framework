#include "mainmenuscene.h"
#include "scenemanager.h"

MainMenuScene::MainMenuScene() {
	// Start game button
	startButton = new Button(Point2(SWIDTH / 2, SHEIGHT / 2 - 200, 10), "assets/StartGameButton.png");
	AddChild(startButton);

	// Enter map builder button
	mapBuilderButton = new Button(Point2(SWIDTH / 2, SHEIGHT / 2, 10), "assets/MapMakerButton.png");
	AddChild(mapBuilderButton);

	// Quit game button
	quitButton = new Button(Point2(SWIDTH / 2, SHEIGHT / 2 + 200, 10), "assets/QuitGameButton.png");
	AddChild(quitButton);
}

MainMenuScene::~MainMenuScene() {
	// Removing created objects
	RemoveChild(startButton);
	delete startButton;
	RemoveChild(mapBuilderButton);
	delete mapBuilderButton;
	RemoveChild(quitButton);
	delete quitButton;
}

void MainMenuScene::SceneLoaded() {
	// Check if a map scene is loaded, and remove it
	if (SceneMaganger::ScenesCount() > 4) {
		SceneMaganger::RemoveScene(4);
	}
}

void MainMenuScene::Update() {
	// Check button input
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