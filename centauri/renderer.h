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
#include "scene.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

class Renderer {
public:
	Renderer();
	virtual ~Renderer();

	void renderScene(Scene* scene);

	GLFWwindow* window() { return _window; };

private:
	unsigned int _VAO;

	ResourceManager _resourcemanager;

	GLFWwindow* _window;

	Shader* _defaultShader;

	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;

	void renderGameObject(glm::mat4 modelMatrix, GameObject* entity, Camera* camera);

	void renderSprite(Camera* camera, glm::mat4 modelMatrix, Sprite* sprite);

	inline void RenderMesh(const glm::mat4 modelMatrix, Shader* shader, Mesh* mesh, GLuint mode);

	int init();
};

#endif
