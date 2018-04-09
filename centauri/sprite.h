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

	GLuint GetTexture() { return _texture; };
	GLuint GetVertexbuffer() { return _vertexbuffer; };
	GLuint GetUvbuffer() { return _uvbuffer; };

	unsigned int GetWidth() { return _width; };
	unsigned int GetHeight() { return _height; };

	std::string GetVertexshader() { return _vertexshader; };
	std::string GetFragmentshader() { return _fragmentshader; };

	void SetVertexshader(std::string vertexshader) { _vertexshader = vertexshader; };
	void SetFragmentshader(std::string fragmentshader) { _fragmentshader = fragmentshader; };

private:
	GLuint _texture;
	GLuint _vertexbuffer;
	GLuint _uvbuffer;

	std::string _vertexshader; // vertexshader (path to the file)
	std::string _fragmentshader; // fragmentshader (path to the file)

	unsigned int _width;
	unsigned int _height;

	GLuint LoadTGA(const std::string& imagepath);
};

#endif
