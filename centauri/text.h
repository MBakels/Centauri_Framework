#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include "font.h"

class Text {
public:
	Text(std::string text, std::string fontPath);
	Text(std::string text, Font font);
	virtual ~Text();

	std::string text;

private:

};

#endif
