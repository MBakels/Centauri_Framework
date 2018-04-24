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

	void setupSprite(std::string image_path, float pivotx, float pivoty, float uvwidth, float uvheight, int filter, int wrap);

	std::string texture() { return _texture; };

	std::string vertexshader() { return _vertexshader; };
	std::string fragmentshader() { return _fragmentshader; };

	void setVertexshader(std::string vertexshader) { _vertexshader = vertexshader; };
	void setFragmentshader(std::string fragmentshader) { _fragmentshader = fragmentshader; };

	void filter(int f) { _filter = f; };
	int filter() { return _filter; };

	void wrap(int w) { _wrap = w; };
	int wrap() { return _wrap; };

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
