#include "text.h"

Text::Text(std::string text, std::string fontPath, RGBAColor textColor) {
	this->text = text;
}

Text::Text(std::string text, Font* font, RGBAColor textColor) {
	this->text = text;
	this->font = font;
	color = textColor;

	_vertexshader = DEFAULTTEXTVERTEXSHADER;
	_fragmentshader = DEFAULTTEXTFRAGMENTSHADER;
	shader = new Shader(_vertexshader.c_str(), _fragmentshader.c_str());
}

Text::~Text() {

}