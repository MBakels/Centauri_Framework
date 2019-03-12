#include "inputfield.h"

InputField::InputField(Point2 size, std::string initialText) {
	// Add sprite
	AddSprite("assets/WhiteSquare.png");
	GetSprite()->size = size;
	// Set text
	text = initialText;
	// Add the text display object
	textObject = new GameObject();
	textObject->AddText(text, "fonts/acari-sans/AcariSans-Regular.ttf");
	textObject->GetText()->verticalAlignment = VerticalAlignment::CenterAlignmentVertical;
	AddChild(textObject);
}

InputField::~InputField() {
	RemoveChild(textObject);
	delete textObject;
}

void InputField::Update() {

}