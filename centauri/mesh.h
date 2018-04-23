#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

class Mesh {
public:
	Mesh();
	virtual ~Mesh();

	GLuint vertexbuffer() { return _vertexbuffer; };
	GLuint uvbuffer() { return _uvbuffer; };

	unsigned int numverts() { return _numverts; };

	void generateSpriteMesh(int width, int height, float pivotx, float pivoty, float uvwidth, float uvheight);

private:
	GLuint _vertexbuffer; // list of vertices
	GLuint _uvbuffer; // list of UV's

	unsigned int _numverts; // number of vertices in the Mesh

	void generateBuffers(std::vector<glm::vec3>& vertex, std::vector<glm::vec2>& uv);
};

#endif
