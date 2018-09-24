#include "sprite.h"

Sprite::Sprite(std::string image_path, float pivotx, float pivoty, float uvwidth, float uvheight, int filter, int wrap) {
	this->SetupSprite(image_path, pivotx, pivoty, uvwidth, uvheight, filter, wrap);
}

void Sprite::SetupSprite(std::string image_path, float pivotx, float pivoty, float uvwidth, float uvheight, int filter, int wrap) {
	pivot = Point2(pivotx, pivoty);
	uvdim = Point2(uvwidth, uvheight);
	uvoffset = Point2(0.0f, 0.0f);
	size = Point2(0.0f, 0.0f);

	_texture = image_path;

	_vertexshader = DEFAULTVERTEXSHADER;
	_fragmentshader = DEFAULTFRAGMENTSHADER;

	_filter = filter;
	_wrap = wrap;

	_animated = false;
	_frame = 0;
	_fps = 30;
	_time = 0;

	color = RGBAColor(255, 255, 255, 255);
}

Sprite::~Sprite() {

}

void Sprite::Update(float deltaTime) {
	if (_animated) {
		_time += deltaTime;
		if (1.0f / _fps < _time) {
			Frame(_frame + 1);
			_time = 0;
		}
	}
}

void Sprite::Frame(int f) {
	int w = 1.0f / uvdim.x;
	int h = 1.0f / uvdim.y;

	if (f >= w * h) {
		_frame = 0;
		uvoffset.x = 0;
		uvoffset.y = 0;
	}

	int ypos = f / w;
	int xpos = f % w;

	uvoffset.x = xpos * uvdim.x;
	uvoffset.y = ypos * uvdim.y;

	_frame = f;
}
