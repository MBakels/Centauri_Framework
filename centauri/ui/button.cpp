#include "ui/button.h"

Button::Button(Point2 position, std::string text, std::string spritePath, RGBAColor color) : GameObject() {
	this->position = position;
	AddSprite(spritePath);
	GetSprite()->color = color;
}

Button::~Button() {
	delete buttonText;
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

void Button::AddButtonText(std::string text, int x, int y, std::string fontPath) {
	buttonText = new GameObject();
	buttonText->AddText(text, fontPath);
	buttonText->position = Vector3(x, y, position.z + 1);
	AddChild(buttonText);
}