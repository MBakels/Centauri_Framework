#include "pausemenu.h"
#include "scenemanager.h"

PauseMenu::PauseMenu() {
	// Menu background sprite
	AddSprite("assets/WhiteSquare.png");
	GetSprite()->color = RGBAColor(0, 0, 0, 130);
	GetSprite()->size = Point2(320, 230);

	// Resume game button
	resumeButton = new Button(Point2(0, -55, 11), "assets/ResumeButton.png");
	AddChild(resumeButton);

	// Back to menu button
	menuButton = new Button(Point2(0, 55, 11), "assets/MenuButton.png");
	AddChild(menuButton);

	//Deactivate self
	SetActive(false);
}

PauseMenu::~PauseMenu() {
	// Removing created objects
	RemoveChild(resumeButton);
	delete resumeButton;
	RemoveChild(menuButton);
	delete menuButton;
}

void PauseMenu::Update(Point2 cameraPos) {
	// Set position to camera position
	position.x = cameraPos.x;
	position.y = cameraPos.y;

	// Check button input
	if (resumeButton->CheckPressed(Point2(GetInput()->GetMouseX() - SWIDTH / 2, GetInput()->GetMouseY() - SHEIGHT / 2))) {
		Toggle();
	}
	if (menuButton->CheckPressed(Point2(GetInput()->GetMouseX() - SWIDTH / 2, GetInput()->GetMouseY() - SHEIGHT / 2))) {
		Toggle(); // Before going to the main menu reset the pause menu
		SceneMaganger::LoadScene(0);
	}
}

void PauseMenu::Toggle() {
	// Toggle timescale and active state
	if (isActive) {
		Time::timeScale = 1;
		SetActive(false);
	} else {
		Time::timeScale = 0;
		SetActive(true);
	}
}