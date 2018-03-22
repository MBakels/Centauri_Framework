#include "config.h"
#include "renderer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Renderer::Renderer() {
	_window = NULL;
	_defaultShader = NULL;

	init();
}

Renderer::~Renderer() {
	glDeleteVertexArrays(1, &VAO);
	glfwTerminate(); // glfw: terminate, clearing all previously allocated GLFW resources.
}

int Renderer::init() {
	// glfw: initialize and configure
	if (!glfwInit()) {
		std::cout << "ERROR::RENDERER::GLFW::GLFW_INIT_FAILED\n" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, RESIZABLE);

	// glfw window creation
	if (FULLSCREEN == 1) {
		_window = glfwCreateWindow(SWIDTH, SHEIGHT, WINDOWNAME, glfwGetPrimaryMonitor(), NULL);
	} else if (FULLSCREEN == 2) {
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		_window = glfwCreateWindow(mode->width, mode->height, WINDOWNAME, monitor, NULL);
	} else {
		_window = glfwCreateWindow(SWIDTH, SHEIGHT, WINDOWNAME, NULL, NULL);
	}
	if (_window == NULL) {
		std::cout << "ERROR::RENDERER::GLFW::FAILED_TO_CREATE_WINDOW\n" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);

	// Initialize glad (load all OpenGL function pointers)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "ERROR::RENDERER::GLAD::FAILED_TO_INIT_GLAD" << std::endl;
		return -1;
	}

	// Set clear color
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	// Create and use shader
	_defaultShader = _resourcemanager.getShader(DEFAULTVERTEXSHADER, DEFAULTFRAGMENTSHADER);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	return 0;
}

void Renderer::renderSprite(Camera* camera, Sprite* sprite, float px, float py, float sx, float sy, float rot) {
	// glm::mat4 viewMatrix = getViewMatrix(); // get from Camera (Camera position and direction)
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	// Build the Model matrix
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(px, py, 0.0f));
	glm::mat4 rotationMatrix = glm::eulerAngleYXZ(0.0f, 0.0f, rot);
	glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(sx, sy, 1.0f));

	modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;

	glm::mat4 MVP = camera->GetProjectionMatrix() * camera->GetViewMatrix() * modelMatrix;

	// Get the shader from the ResourceManager
	Shader* shader = _resourcemanager.getShader(sprite->vertexshader().c_str(), sprite->fragmentshader().c_str());
	if (shader == NULL) {
		shader = _defaultShader; // fallback to defaultshader
	}
	shader->Use();

	// Send transformation to the currently bound shader
	_defaultShader->setMat4("MVP", MVP);

	// Binding texture to Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sprite->texture());
	_defaultShader->SetInt("texture", 0);

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, sprite->vertexbuffer());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, sprite->uvbuffer());
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 2 * 3); // 2*3 indices starting at 0 -> 2 triangles

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
