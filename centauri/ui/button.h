#ifndef BUTTON_H
#define BUTTON_H

#include "gameobject.h"

class Button : public GameObject {
public:
	Button(Point2 position, std::string text, std::string spritePath, RGBAColor color = WHITE);

	virtual ~Button();

	bool CheckPressed(Point2 mousePos);

	void AddButtonText(std::string text, int x = 0, int y = 0, std::string fontPath = "fonts/acari-sans/AcariSans-Regular.ttf");

private:
	GameObject* buttonText;

};

#endif
