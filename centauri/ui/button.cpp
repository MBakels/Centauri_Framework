#include "ui/button.h"

Button::~Button() {

}

void Button::CheckIfPressed(Point2 mousePos) {
	Point2 size = GetSprite()->size;
	if (mousePos.x >= position.x + size.x && mousePos.x < position.x - size.x && mousePos.y >= position.y + size.y && mousePos.y < position.y - size.y) {
		OnClick();
	}
}

void Button::OnClick() {
	//callback_func();
}