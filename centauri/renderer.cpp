#include "renderer.h"
#include "config.h"

Renderer::Renderer() {
	_window = NULL;
	//_defaultShader = NULL;

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

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	return 0;
}

void Renderer::RenderScene(Scene* scene) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear screen
	_viewMatrix = scene->GetCamera()->ViewMatrix(); // Get viewMatrix from camera
	_projectionMatrix = scene->GetCamera()->ProjectionMatrix(); // Get projectionMatrix from camera

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
	std::vector<GameObject*> children = entity->Children();
	std::vector<GameObject*>::iterator child;
	for (child = children.begin(); child != children.end(); child++) {
		this->RenderGameObject(modelMatrix, *child, camera);
	}
}

void Renderer::RenderSprite(Camera* camera, glm::mat4 modelMatrix, Sprite* sprite) {
	Shader* shader = _resourcemanager.GetShader(sprite->Vertexshader().c_str(), sprite->Fragmentshader().c_str());

	Texture* texture = _resourcemanager.GetTexture(sprite->GetTexture(), sprite->Filter(), sprite->Wrap());
	if (sprite->size.x == 0) { sprite->size.x = texture->Width() * sprite->uvdim.x; }
	if (sprite->size.y == 0) { sprite->size.y = texture->Height() * sprite->uvdim.y; }

	Mesh* mesh = _resourcemanager.GetSpriteMesh(sprite->size.x, sprite->size.y, sprite->pivot.x, sprite->pivot.y, sprite->uvdim.x, sprite->uvdim.y);

	shader->SetVec2("UVoffset", sprite->uvoffset.x, sprite->uvoffset.y); // Set uvoffset

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->GetTexture());

	RenderMesh(modelMatrix, shader, mesh, GL_TRIANGLES);
}

void Renderer::RenderMesh(const glm::mat4 modelMatrix, Shader* shader, Mesh* mesh, GLuint mode) {
	shader->Use(); // Use the shader

	glm::mat4 MVP = _projectionMatrix * _viewMatrix * modelMatrix; // Create MVP matrix

	shader->SetMat4("MVP", MVP); // Send transformation to the currently bound shader

	shader->SetInt("texture", 0); // Set the "texture" sampler to user Texture Unit 0

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->GetVertexbuffer());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->GetUvbuffer());
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(mode, 0, mesh->GetNumverts());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
