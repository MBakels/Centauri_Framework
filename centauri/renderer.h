#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
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

	void RenderScene(Scene* scene);

	GLFWwindow* GetWindow() { return _window; };

private:
	unsigned int _VAO;

	ResourceManager _resourcemanager;

	GLFWwindow* _window;

	Shader* _defaultShader;

	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;

	void RenderGameObject(glm::mat4 modelMatrix, GameObject* entity, Camera* camera);

	void RenderSprite(Camera* camera, glm::mat4 modelMatrix, Sprite* sprite);

	void RenderBasicShape(Camera* camera, glm::mat4 modelMatrix, BasicShapes* basicShape);

	inline void RenderMesh(const glm::mat4 modelMatrix, Shader* shader, Mesh* mesh, GLuint mode);

	int Init();
};

#endif
