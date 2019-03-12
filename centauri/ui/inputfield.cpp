#include "inputfield.h"

InputField::InputField(Point3 position, Point2 size, std::string initialText) {
	// Set position
	this->position = position;
	// Add sprite
	AddSprite("assets/WhiteSquare.png");
	GetSprite()->size = size;
	// Set text
	text = initialText;
	// Add the text display object
	textObject = new GameObject();
	textObject->position = Point3(-size.x / 2, 0, 5);
	textObject->AddText(text, "fonts/acari-sans/AcariSans-Regular.ttf");
	textObject->GetText()->verticalAlignment = VerticalAlignment::CenterAlignmentVertical;
	textObject->GetText()->color = BLACK;
	AddChild(textObject);

	// Set selected to false
	selected = false;
}

InputField::~InputField() {
	// Removing text object
	RemoveChild(textObject);
	delete textObject;
}

void InputField::Update() {
	// Check if the mouse press is on this object
	if (GetInput()->GetMouseDown(0)) {
		Point2 halfSize = GetSprite()->size / 2;
		float mousePosX = GetInput()->GetMouseX();
		float mousePosY = GetInput()->GetMouseY();
		// If the object is pressed set selected to true.
		// If the object was already selected and we pressed somewhere not on the object set selected to false
		if (selected == false && mousePosX <= position.x + halfSize.x && mousePosX > position.x - halfSize.x && mousePosY <= position.y + halfSize.y && mousePosY > position.y - halfSize.y) {
			selected = true;
		} else if (selected == true && !(mousePosX <= position.x + halfSize.x && mousePosX > position.x - halfSize.x && mousePosY <= position.y + halfSize.y && mousePosY > position.y - halfSize.y)) {
			selected = false;
		}
	}
}