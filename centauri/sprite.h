#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <iostream>
#include <glad/glad.h>

class Sprite {
public:
	Sprite();
	Sprite(std::string image_path);
	virtual ~Sprite();

	GLuint texture() { return _texture; };
	GLuint vertexbuffer() { return _vertexbuffer; };
	GLuint uvbuffer() { return _uvbuffer; };

	unsigned int width() { return _width; };
	unsigned int height() { return _height; };

	std::string vertexshader() { return _vertexshader; };
	std::string fragmentshader() { return _fragmentshader; };

	void setVertexshader(std::string vertexshader) { _vertexshader = vertexshader; };
	void setFragmentshader(std::string fragmentshader) { _fragmentshader = fragmentshader; };

private:
	GLuint _texture;
	GLuint _vertexbuffer;
	GLuint _uvbuffer;

	std::string _vertexshader; // vertexshader (path to the file)
	std::string _fragmentshader; // fragmentshader (path to the file)

	unsigned int _width;
	unsigned int _height;

	GLuint loadTGA(const std::string& imagepath);
};

#endif
