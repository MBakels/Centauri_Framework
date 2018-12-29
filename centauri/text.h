#ifndef TEXT_H
#define TEXT_H

#include <iostream>

#include "config.h"
#include "font.h"
#include "color.h"

#include "shader.h"

class Text {
public:
	Text(std::string text, std::string fontPath, RGBAColor textColor = WHITE);
	Text(std::string text, Font* font, RGBAColor textColor = WHITE);
	virtual ~Text();

	std::string Vertexshader() { return _vertexshader; };
	std::string Fragmentshader() { return _fragmentshader; };

	void Vertexshader(std::string vertexshader) { _vertexshader = vertexshader; };
	void Fragmentshader(std::string fragmentshader) { _fragmentshader = fragmentshader; };

	std::string text;
	RGBAColor color;
	Font* font;
	Shader* shader;

private:
	std::string _vertexshader;
	std::string _fragmentshader;

};

#endif
