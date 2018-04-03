
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
#include "gameobject.h"

class Renderer {
public:
	Renderer();
	virtual ~Renderer();

	void RenderEntity(glm::mat4 modelMatrix, GameObject* entity, Camera* camera);

	//void RenderSprite(Camera* camera, Sprite* sprite, float px, float py, float sx, float sy, float rot);
	void RenderSprite(Camera* camera, glm::mat4 modelMatrix, Sprite* sprite);

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
