
#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "resourcemanager.h"
#include "sprite.h"
#include "shader.h"
#include "camera.h"

class Renderer {
public:
	Renderer();
	virtual ~Renderer();

	void renderSprite(Camera* camera, Sprite* sprite, float px, float py, float sx, float sy, float rot);

	GLFWwindow* window() { return _window; };

private:
	unsigned int VAO;

	ResourceManager _resourcemanager;

	GLFWwindow* _window;

	Shader* _defaultShader;

	int init();

	//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

#endif
