#include "text.h"

Text::Text(std::string text, std::string fontPath, int fontSize, RGBAColor textColor) {
	this->text = text;
	this->fontPath = fontPath;
	this->fontSize = fontSize;
	color = textColor;

	verticalAlignment = VerticalAlignment::BottomAlignment;
	horizontalAlignment = HorizontalAlignment::LeftAlignment;

	_vertexshader = DEFAULTTEXTVERTEXSHADER;
	_fragmentshader = DEFAULTTEXTFRAGMENTSHADER;
}

Text::~Text() {

}