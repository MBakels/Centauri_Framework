#include "winmenuscene.h"
#include "scenemanager.h"

WinMenuScene::WinMenuScene() {
	// Back to menu button
	menuButton = new Button(Point2(SWIDTH / 2, SHEIGHT / 2 + 100, -1), "assets/WhiteSquare.png", BLACK);
	menuButton->GetSprite()->size = Point2(300, 100);
	menuButton->AddButtonText("Menu", 0, 0, 62);
	AddChild(menuButton);

	// Text message
	text = new GameObject();
	text->position = Vector3(SWIDTH / 2 - 400, SHEIGHT / 2 - 100, 0);
	text->AddText("You won! go back to the menu\nand try a different level", "fonts/acari-sans/AcariSans-Regular.ttf", 62);
	AddChild(text);
}

WinMenuScene::~WinMenuScene() {
	// Removing created objects
	RemoveChild(menuButton);
	delete menuButton;
	RemoveChild(text);
	delete text;
}

void WinMenuScene::Update() {
	// Check button input
	if (menuButton->CheckPressed(Point2(GetInput()->GetMouseX(), GetInput()->GetMouseY()))) {
		SceneMaganger::LoadScene(0);
	}
}