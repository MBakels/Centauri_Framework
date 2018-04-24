#include "config.h"
#include "sprite.h"

Sprite::Sprite(std::string image_path) {
	this->setupSprite(image_path, 0.5f, 0.5f, 1.0f, 1.0f, DEFAULTFILTER, DEFAULTWRAP);
}

void Sprite::setupSprite(std::string image_path, float pivotx, float pivoty, float uvwidth, float uvheight, int filter, int wrap) {
	pivot = Point2(pivotx, pivoty);
	uvdim = Point2(uvwidth, uvheight);
	uvoffset = Point2(0.0f, 0.0f);
	size = Point2(0.0f, 0.0f);

	_texture = image_path;

	_vertexshader = DEFAULTVERTEXSHADER;
	_fragmentshader = DEFAULTFRAGMENTSHADER;

	_filter = filter;
	_wrap = wrap;
}

Sprite::~Sprite() {

}
