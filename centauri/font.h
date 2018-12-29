#ifndef FONT_H
#define FONT_H

#include <glad/glad.h>
#include <iostream>
#include "vectorx.h"
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H 

struct Character {
	GLuint TextureID; // ID handle of the glyph texture
	Vector2 Size; // Size of glyph
	Vector2 Bearing; // Offset from baseline to left/top of glyph
	GLuint Advance; // Offset to advance to next glyph
};

class Font {
public:
	Font(const char* fontPath, int fontSize = 48, int numberOfCharactersToLoad = 128);
	virtual ~Font();

	std::map<char, Character> Characters;
};

#endif
