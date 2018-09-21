#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <iostream>
#include <glad/glad.h>

#include "config.h"
#include "pointx.h"
#include "centauri/color.h"

class Sprite {
public:
	Sprite(std::string image_path, float pivotx = 0.5f, float pivoty = 0.5f, float uvwidth = 1.0f, float uvheight = 1.0f, int filter = DEFAULTFILTER, int wrap = DEFAULTWRAP);
	virtual ~Sprite();

	void Update(float deltaTime);

	std::string GetTexture() { return _texture; };

	std::string Vertexshader() { return _vertexshader; };
	std::string Fragmentshader() { return _fragmentshader; };

	void Vertexshader(std::string vertexshader) { _vertexshader = vertexshader; };
	void Fragmentshader(std::string fragmentshader) { _fragmentshader = fragmentshader; };

	void Filter(int f) { _filter = f; };
	int Filter() { return _filter; };

	void Wrap(int w) { _wrap = w; };
	int Wrap() { return _wrap; };

	void IsAnimated(bool a) { _animated = a; };

	int frame(int f);
	int frame() { return _frame; };

	int fps(int fps) { _fps = fps; };

	Point2 pivot;
	Point2 uvdim;
	Point2 uvoffset;
	Point2 size;
	RGBAColor color; // blend Color of the Sprite

private:
	std::string _texture;

	std::string _vertexshader; // vertexshader (path to the file)
	std::string _fragmentshader; // fragmentshader (path to the file)

	int _filter;
	int _wrap;

	bool _animated; // is the sprite animated
	int _frame; // current frame of the animated sprite
	int _fps; // frames per second for the animated sprite
	float _time; // keeps track of time since last frame swap

	void SetupSprite(std::string image_path, float pivotx, float pivoty, float uvwidth, float uvheight, int filter, int wrap);
};

#endif
