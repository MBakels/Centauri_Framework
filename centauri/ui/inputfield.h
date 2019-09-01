#ifndef INPUTFIELD_H
#define INPUTFIELD_H

#include "gameobject.h"

class InputField : public GameObject {
public:
	// Constructor of the InputField class
	InputField(Point3 position, Point2 size, std::string initialText);
	// Destructor of the InputField class
	virtual ~InputField();

	// Updates the input field
	void Update();

	// The text value of the InputField
	std::string text;

private:
	// Object to hold the text to display
	GameObject* textObject;

	// Is this object currently selected?
	bool selected;
};

#endif