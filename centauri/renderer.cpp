#include "renderer.h"
#include "config.h"

Renderer::Renderer() {
	_window = NULL;
	_defaultShader = NULL;

	Init();
}

Renderer::~Renderer() {
	glDeleteVertexArrays(1, &_VAO);
	glfwTerminate(); // glfw: terminate, clearing all previously allocated GLFW resources.
}

int Renderer::Init() {
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
	glfwSetFramebufferSizeCallback(_window, FramebufferSizeCallback);

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
	_defaultShader = _resourcemanager.GetShader(DEFAULTVERTEXSHADER, DEFAULTFRAGMENTSHADER);

	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	return 0;
}

void Renderer::RenderScene(Scene* scene) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear screen
	_viewMatrix = scene->GetCamera()->GetViewMatrix(); // Get viewMatrix from camera
	_projectionMatrix = scene->GetCamera()->GetProjectionMatrix(); // Get projectionMatrix from camera

	glm::mat4 modelMatrix = glm::mat4(1.0f); // The root scene has a identity matrix

	this->RenderGameObject(modelMatrix, scene, scene->GetCamera());
	
	glfwSwapBuffers(_window); // Swap buffers
}

void Renderer::RenderGameObject(glm::mat4 modelMatrix, GameObject* entity, Camera* camera) {
	// Translate Point3 to glm::vec3
	glm::vec3 position = glm::vec3(entity->position.x, entity->position.y, entity->position.z);
	glm::vec3 rotation = glm::vec3(entity->rotation.x, entity->rotation.y, entity->rotation.z);
	glm::vec3 scale = glm::vec3(entity->scale.x, entity->scale.y, entity->scale.z);

	// Building model matrix
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotationMatrix = glm::eulerAngleYXZ(rotation.y, rotation.x, rotation.z);
	glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), scale);

	glm::mat4 mm = translationMatrix * rotationMatrix * scalingMatrix;
	modelMatrix *= mm;

	// Check for Sprite
	Sprite* sprite = entity->GetSprite();
	if (sprite != NULL) {
		this->RenderSprite(camera, modelMatrix, sprite);
	}

	// Render all Children
	std::vector<GameObject*> children = entity->GetChildren();
	std::vector<GameObject*>::iterator child;
	for (child = children.begin(); child != children.end(); child++) {
		this->RenderGameObject(modelMatrix, *child, camera);
	}
}

void Renderer::RenderSprite(Camera* camera, glm::mat4 modelMatrix, Sprite* sprite){
	glm::mat4 MVP = camera->GetProjectionMatrix() * camera->GetViewMatrix() * modelMatrix;

	// Get the shader from the ResourceManager
	Shader* shader = _resourcemanager.GetShader(sprite->GetVertexshader().c_str(), sprite->GetFragmentshader().c_str());
	if (shader == NULL) {
		shader = _defaultShader; // fallback to defaultshader
	}
	shader->Use();

	// Send transformation to the currently bound shader
	_defaultShader->setMat4("MVP", MVP);

	// Binding texture to Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sprite->GetTexture());
	_defaultShader->SetInt("texture", 0);

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, sprite->GetVertexbuffer());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, sprite->GetUvbuffer());
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 2 * 3); // 2*3 indices starting at 0 -> 2 triangles

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
