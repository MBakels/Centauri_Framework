#include "deathmenuscene.h"
#include "scenemanager.h"

DeathMenuScene::DeathMenuScene() {
	// Back to menu button
	menuButton = new Button(Point2(SWIDTH / 2, SHEIGHT / 2 + 100, -1), "assets/WhiteSquare.png", BLACK);
	menuButton->GetSprite()->size = Point2(300, 100);
	menuButton->AddButtonText("Menu", -75, -40, 62);
	AddChild(menuButton);

	// Text message
	text = new GameObject();
	text->position = Vector3(SWIDTH / 2 - 575, SHEIGHT / 2 - 100, 0);
	text->AddText("You lost go back to the menu and try again", "fonts/acari-sans/AcariSans-Regular.ttf", 62);
	AddChild(text);
}

DeathMenuScene::~DeathMenuScene() {
	// Removing created objects
	RemoveChild(menuButton);
	delete menuButton;
	RemoveChild(text);
	delete text;
}

void DeathMenuScene::Update() {
	// Check button input
	if (menuButton->CheckPressed(Point2(GetInput()->GetMouseX(), GetInput()->GetMouseY()))) {
		SceneMaganger::LoadScene(0);
	}
}