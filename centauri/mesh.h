#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "vectorx.h"

class Mesh {
public:
	Mesh();
	virtual ~Mesh();

	GLuint GetVertexbuffer() { return _vertexbuffer; };
	GLuint GetUvbuffer() { return _uvbuffer; };

	unsigned int GetNumverts() { return _numverts; };

	void GenerateSpriteMesh(int width, int height, float pivotx, float pivoty, float uvwidth, float uvheight);

	void GenerateCircleMesh(int radius, int segments, float pivotx, float pivoty, float uvwidth, float uvheight);

private:
	GLuint _vertexbuffer; // list of vertices
	GLuint _uvbuffer; // list of UV's

	unsigned int _numverts; // number of vertices in the Mesh

	void GenerateBuffers(std::vector<glm::vec3>& vertex, std::vector<glm::vec2>& uv);
};

#endif
