#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <iostream>
#include <GLFW/glfw3.h>

class Texture {
public:
	Texture();
	virtual ~Texture();

	GLuint GetTexture() { return _gltexture; };

	int Width() { return _width; };
	int Height() { return _height; };
	int Depth() { return _bitdepth; };

	GLuint LoadTGA(const std::string& filename, int filter, int wrap);

private:
	int _width;
	int _height;
	int _bitdepth;

	GLuint _gltexture;
};

#endif
