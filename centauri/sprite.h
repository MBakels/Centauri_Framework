#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <iostream>
#include <glad/glad.h>

#include "pointx.h"

class Sprite {
public:
	Sprite(std::string image_path);
	virtual ~Sprite();

	void SetupSprite(std::string image_path, float pivotx, float pivoty, float uvwidth, float uvheight, int filter, int wrap);

	std::string GetTexture() { return _texture; };

	std::string Vertexshader() { return _vertexshader; };
	std::string Fragmentshader() { return _fragmentshader; };

	void Vertexshader(std::string vertexshader) { _vertexshader = vertexshader; };
	void Fragmentshader(std::string fragmentshader) { _fragmentshader = fragmentshader; };

	void Filter(int f) { _filter = f; };
	int Filter() { return _filter; };

	void Wrap(int w) { _wrap = w; };
	int Wrap() { return _wrap; };

	Point2 pivot;
	Point2 uvdim;
	Point2 uvoffset;
	Point2 size;

private:
	std::string _texture;

	std::string _vertexshader; // vertexshader (path to the file)
	std::string _fragmentshader; // fragmentshader (path to the file)

	int _filter;
	int _wrap;
};

#endif
