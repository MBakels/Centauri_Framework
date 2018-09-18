#include "basicshapes.h"

BasicShapes::BasicShapes() {
	pivot = Point2(0.5f, 0.5f);
	uvdim = Point2(1.0f, 1.0f);
	uvoffset = Point2(0.0f, 0.0f);
	size = Point2(0.0f, 0.0f);
	radius = 0;
	segments = 0;

	_vertexshader = DEFAULTVERTEXSHADER;
	_fragmentshader = "shaders/temp_frag_shader.frag";//DEFAULTFRAGMENTSHADER;
}

BasicShapes::~BasicShapes() {

}

void BasicShapes::CreateCircle(int radius, int segments, float pivotx, float pivoty, float uvwidth, float uvheight) {
	this->radius = radius;
	this->segments = segments;
	pivot = Point2(pivotx, pivoty);
	uvdim = Point2(uvwidth, uvheight);
	size = Point2(radius * 2, radius * 2);
}

void BasicShapes::CreateTriangle(int size, float pivotx, float pivoty, float uvwidth, float uvheight) {
	CreateCircle(size / 2, 3, pivotx, pivoty, uvwidth, uvheight);
}