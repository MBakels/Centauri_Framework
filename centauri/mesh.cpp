#include "mesh.h"

Mesh::Mesh() {
	_vertexbuffer = 0;
	_uvbuffer = 0;

	_numverts = 0;
}

Mesh::~Mesh() {
	if (_vertexbuffer != 0) {
		glDeleteBuffers(1, &_vertexbuffer);
		glDeleteBuffers(1, &_uvbuffer);
	}
}

void Mesh::GenerateSpriteMesh(int width, int height, float pivotx, float pivoty, float uvwidth, float uvheight) {
	_numverts = 6;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;

	// first triangle
	vertices.push_back(glm::vec3(-width * pivotx, -height * pivoty, 1.0f));
	vertices.push_back(glm::vec3(-width * pivotx, height - (height * pivoty), 1.0f));
	vertices.push_back(glm::vec3(width - (width * pivotx), height - (height * pivoty), 1.0f));
	// second triangle
	vertices.push_back(glm::vec3(width - (width * pivotx), height - (height * pivoty), 1.0f));
	vertices.push_back(glm::vec3(width - (width * pivotx), -height * pivoty, 1.0f));
	vertices.push_back(glm::vec3(-width * pivotx, -height * pivoty, 1.0f));

	// UV coordinates for each vertex.
	// uvs for first triangle
	uvs.push_back(glm::vec2(0.0f, uvheight));
	uvs.push_back(glm::vec2(0.0f, 0.0f));
	uvs.push_back(glm::vec2(uvwidth, 0.0f));
	// uvs for second triangle
	uvs.push_back(glm::vec2(uvwidth, 0.0f));
	uvs.push_back(glm::vec2(uvwidth, uvheight));
	uvs.push_back(glm::vec2(0.0f, uvheight));

	this->GenerateBuffers(vertices, uvs);
}

void Mesh::GenerateCircleMesh(int radius, int segments, float pivotx, float pivoty, float uvwidth, float uvheight) {
	_numverts = segments * 3;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;

	pivotx -= 0.5f;
	pivoty -= 0.5f;

	float x = 0.0f;
	float y = 0.0f;
	float u = 0.5f;
	float v = 0.5f;
	float deg = 360;

	for (unsigned int i = 0; i < segments; i++) {
		vertices.push_back(glm::vec3(pivotx * 2 * radius, pivoty * 2 * radius, 0.0f));
		uvs.push_back(glm::vec2(0.5f, 0.5f));

		x = cos(deg * DEG_TO_RAD) * radius;
		y = sin(deg * DEG_TO_RAD) * radius;
		u = (x / radius) * uvwidth;
		v = (-y / radius) * uvheight;
		vertices.push_back(glm::vec3(x + (pivotx * 2 * radius), y + (pivoty * 2 * radius), 0.0f));
		uvs.push_back(glm::vec2(u / 2 + 0.5f, v / 2 + 0.5f));

		deg -= 360.0f / segments;
		x = cos(deg * DEG_TO_RAD) * radius;
		y = sin(deg * DEG_TO_RAD) * radius;
		u = (x / radius) * uvwidth;
		v = (-y / radius) * uvheight;
		vertices.push_back(glm::vec3(x + (pivotx * 2 * radius), y + (pivoty * 2 * radius), 0.0f));
		uvs.push_back(glm::vec2(u / 2 + 0.5f, v / 2 + 0.5f));
	}

	this->GenerateBuffers(vertices, uvs);
}

void Mesh::GenerateBuffers(std::vector<glm::vec3>& vertex, std::vector<glm::vec2>& uv) {
	//create GLuint _vertexbuffer;
	glGenBuffers(1, &_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(glm::vec3), &vertex[0], GL_STATIC_DRAW);

	//create GLuint _uvbuffer;
	glGenBuffers(1, &_uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(glm::vec2), &uv[0], GL_STATIC_DRAW);
}
