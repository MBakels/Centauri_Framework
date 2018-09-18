#ifndef BASICSHAPES_H
#define BASICSHAPES_H

#include "config.h"
#include "pointx.h"

class BasicShapes {
public:
	BasicShapes();
	virtual ~BasicShapes();

	void CreateCircle(int radius, int segments, float pivotx = 0.5f, float pivoty = 0.5f, float uvwidth = 1.0f, float uvheight = 1.0f);
	void CreateTriangle(int size, float pivotx = 0.5f, float pivoty = 0.5f, float uvwidth = 1.0f, float uvheight = 1.0f);

	std::string Vertexshader() { return _vertexshader; };
	std::string Fragmentshader() { return _fragmentshader; };

	void Vertexshader(std::string vertexshader) { _vertexshader = vertexshader; };
	void Fragmentshader(std::string fragmentshader) { _fragmentshader = fragmentshader; };

	Point2 pivot;
	Point2 uvdim;
	Point2 uvoffset;
	Point2 size;
	int radius;
	int segments;

private:
	std::string _vertexshader; // vertexshader (path to the file)
	std::string _fragmentshader; // fragmentshader (path to the file)

};

#endif
