#ifndef TEXT_H
#define TEXT_H

#include <iostream>

#include "config.h"
#include "font.h"
#include "color.h"

#include "shader.h"

enum VerticalAlignment {
	TopAlignment,
	CenterAlignmentVertical,
	BottomAlignment
};

enum HorizontalAlignment {
	LeftAlignment,
	CenterAlignmentHorizontal,
	RightAlignment
};

class Text {
public:
	Text(std::string text, std::string fontPath, int fontSize, RGBAColor textColor);
	virtual ~Text();

	std::string Vertexshader() { return _vertexshader; };
	std::string Fragmentshader() { return _fragmentshader; };

	void Vertexshader(std::string vertexshader) { _vertexshader = vertexshader; };
	void Fragmentshader(std::string fragmentshader) { _fragmentshader = fragmentshader; };

	std::string text;
	RGBAColor color;
	std::string fontPath;
	int fontSize;
	VerticalAlignment verticalAlignment;
	HorizontalAlignment horizontalAlignment;

private:
	std::string _vertexshader;
	std::string _fragmentshader;

};

#endif
