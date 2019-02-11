#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "resourcemanager.h"
#include "shader.h"
#include "scene.h"

struct TransparentRenderable {
	glm::mat4 modelMatrix;
	Sprite* sprite;
	Texture* texture;

	TransparentRenderable() {
		modelMatrix = glm::mat4(1.0f);
		sprite = NULL;
		texture = NULL;
	}

	TransparentRenderable(glm::mat4 mm, Sprite* spr, Texture* tex) {
		modelMatrix = mm;
		sprite = spr;
		texture = tex;
	}
};

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

class Renderer {
public:
	Renderer();
	virtual ~Renderer();

	void RenderScene(Scene* scene);

	GLFWwindow* GetWindow() { return _window; };

private:
	GLuint _framebuffer;
	GLuint _renderbuffer;
	GLuint _texColorBuffer;
	GLuint _framebufferVAO, _framebufferVBO;

	GLuint _spriteVAO;
	GLuint _textVAO, _textVBO;

	ResourceManager _resourcemanager;

	GLFWwindow* _window;

	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;

	std::multimap<float, TransparentRenderable> transparentRenderableSpriteList;

	void RenderGameObject(glm::mat4 modelMatrix, GameObject* entity, Camera* camera);

	void RenderSprite(glm::mat4 modelMatrix, Sprite* sprite, Texture* texture);

	void RenderText(Text* text, GLfloat x, GLfloat y);

	void RenderBasicShape(glm::mat4 modelMatrix, BasicShapes* basicShape);

	inline void RenderMesh(const glm::mat4 modelMatrix, Shader* shader, Mesh* mesh, GLuint mode, RGBAColor blendcolor);

	int Init();
};

#endif
