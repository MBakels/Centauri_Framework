#ifndef BUTTON_H
#define BUTTON_H

#include "gameobject.h"

class Button : public GameObject {
public:
	template<class T>
	Button(Point2 position, std::string text, std::string spritePath, void(T::*callback_func)()) {
		AddSprite(spritePath);
		//this->callback_func = callback_func;
		std::cout << "testing buttons" << std::endl;
	}

	virtual ~Button();

	void CheckIfPressed(Point2 mousePos);

	void OnClick();

private:
	template<class T>
	void(T::*callback_func)();

};

#endif