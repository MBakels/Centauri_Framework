#include "ui/button.h"

Button::Button(Point2 position, std::string spritePath, RGBAColor color) : GameObject() {
	this->position = position;
	AddSprite(spritePath);
	GetSprite()->color = color;
	buttonText = NULL;
}

Button::~Button() {
	if (buttonText != NULL) {
		delete buttonText;
	}
}

bool Button::CheckPressed(Point2 mousePos) {
	if (GetInput()->GetMouseDown(0)) {
		Point2 halfSize = GetSprite()->size / 2;
		if (mousePos.x <= position.x + halfSize.x && mousePos.x > position.x - halfSize.x && mousePos.y <= position.y + halfSize.y && mousePos.y > position.y - halfSize.y) {
			return true;
		}
	}
	return false;
}

void Button::AddButtonText(std::string text, int x, int y, int fontSize, std::string fontPath) {
	buttonText = new GameObject();
	buttonText->AddText(text, fontPath, fontSize);
	buttonText->position = Vector3(x, y, 2);
	AddChild(buttonText);
}