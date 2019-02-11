#include "renderer.h"
#include "config.h"

Renderer::Renderer() {
	_window = NULL;
	Init();
}

Renderer::~Renderer() {
	glDeleteVertexArrays(1, &_spriteVAO);
	glDeleteVertexArrays(1, &_textVAO);
	glDeleteBuffers(1, &_textVBO);
	glDeleteFramebuffers(1, &_framebuffer);
	glDeleteRenderbuffers(1, &_renderbuffer);
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
	glfwWindowHint(GLFW_SAMPLES, MSAA);

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

	// Vertical synchronisation
	glfwSwapInterval(VSYNC);

	// Set clear color
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Enable MSAA
	glEnable(GL_MULTISAMPLE);

	// Enable blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// Sprite VAO
	glGenVertexArrays(1, &_spriteVAO);

	// Text VAO and VBO
	glGenVertexArrays(1, &_textVAO);
	glGenBuffers(1, &_textVBO);
	glBindVertexArray(_textVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _textVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// setting unpack alignment
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Creating a framebuffer (this is the framebuffer we draw to, the default framebuffer is used for rendering)
	glGenFramebuffers(1, &_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

	// Generate texture for framebuffer
	glGenTextures(1, &_texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, _texColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SWIDTH, SHEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Attach the texture to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texColorBuffer, 0);

	// Creating a renderbuffer object for the depth and stencil attachment(renderbuffer objects are more optimized but you cant sample them)
	glGenRenderbuffers(1, &_renderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, _renderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SWIDTH, SHEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// Attach the rbo to the framebuffer
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _renderbuffer);

	// Check if the framebuffer is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}
	// Unbind the framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
	float quadVertices[] = {
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	// Screen quad VAO for framebuffer
	glGenVertexArrays(1, &_framebufferVAO);
	glGenBuffers(1, &_framebufferVBO);
	glBindVertexArray(_framebufferVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _framebufferVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glBindVertexArray(0);

	// Draw in wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	return 0;
}

void Renderer::RenderScene(Scene* scene) {
	// First pass
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear screen
	glEnable(GL_DEPTH_TEST);

	_viewMatrix = scene->GetCamera()->ViewMatrix(); // Get viewMatrix from camera
	_projectionMatrix = scene->GetCamera()->ProjectionMatrix(); // Get projectionMatrix from camera

	glm::mat4 modelMatrix = glm::mat4(1.0f); // The root scene has a identity matrix

	// Render the scene
	this->RenderGameObject(modelMatrix, scene, scene->GetCamera());

	// Render transparent sprites in reverse order
	for (std::multimap<float, TransparentRenderable>::reverse_iterator it = transparentRenderableSpriteList.rbegin(); it != transparentRenderableSpriteList.rend(); ++it) {
		TransparentRenderable tr = it->second;
		this->RenderSprite(tr.modelMatrix, tr.sprite, tr.texture);
	}
	transparentRenderableSpriteList.clear();

	// Second pass
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // Back to default framebuffer
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	Shader* framebufferShader = _resourcemanager.GetShader(DEFAULTFRAMEBUFFERVERTEXSHADER, DEFAULTFRAMEBUFFERFRAGMENTSHADER);
	framebufferShader->Use();
	glBindVertexArray(_framebufferVAO);
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, _texColorBuffer);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glfwSwapBuffers(_window); // Swap buffers
}

void Renderer::RenderGameObject(glm::mat4 modelMatrix, GameObject* entity, Camera* camera) {
	// Stop rendering if the gameobject is inactive
	if (!entity->isActive) return;

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
		// Check for transparent sprites and puth them in a list(they need to be rendered last)
		Texture* texture = _resourcemanager.GetTexture(sprite->GetTexture(), sprite->Filter(), sprite->Wrap());
		if (texture->Depth() == 4) {
			float distance = glm::length(camera->position.z - entity->position.z);
			transparentRenderableSpriteList.insert(std::pair<float, TransparentRenderable>(distance, TransparentRenderable(modelMatrix, sprite, texture)));
		} else {
			this->RenderSprite(modelMatrix, sprite, texture);
		}
	}

	// Check for Text
	Text* text = entity->GetText();
	if (text != NULL) {
		this->RenderText(text, position.x, position.y);
	}

	// Check for BasicShapes
	BasicShapes* basicShape = entity->GetBasicShape();
	if (basicShape != NULL) {
		this->RenderBasicShape(modelMatrix, basicShape);
	}

	// Render all Children
	std::vector<GameObject*> children = entity->Children();
	std::vector<GameObject*>::iterator child;
	for (child = children.begin(); child != children.end(); child++) {
		this->RenderGameObject(modelMatrix, *child, camera);
	}
}

void Renderer::RenderSprite(glm::mat4 modelMatrix, Sprite* sprite, Texture* texture) {
	if (sprite->size.x == 0) { sprite->size.x = texture->Width() * sprite->uvdim.x; }
	if (sprite->size.y == 0) { sprite->size.y = texture->Height() * sprite->uvdim.y; }

	Shader* shader = _resourcemanager.GetShader(sprite->Vertexshader().c_str(), sprite->Fragmentshader().c_str());
	shader->Use();
	shader->SetVec2("UVoffset", sprite->uvoffset.x, sprite->uvoffset.y); // Set uvoffset

	Mesh* mesh = _resourcemanager.GetMesh(sprite->size.x, sprite->size.y, sprite->pivot.x, sprite->pivot.y, sprite->uvdim.x, sprite->uvdim.y, 0);

	RGBAColor blendcolor = sprite->color;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->GetTexture());

	glBindVertexArray(_spriteVAO);
	RenderMesh(modelMatrix, shader, mesh, GL_TRIANGLES, blendcolor);
	glBindVertexArray(0);
}

void Renderer::RenderText(Text* text, GLfloat x, GLfloat y) {
	Shader* shader = _resourcemanager.GetShader(text->Vertexshader().c_str(), text->Fragmentshader().c_str());
	shader->Use();
	shader->SetVec3("textColor", (float)text->color.r / 255.0f, (float)text->color.g / 255.0f, (float)text->color.b / 255.0f);
	shader->SetMat4("projection", _projectionMatrix);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(_textVAO);

	// Number of enter characters passed in text
	int enterCounter = 0;
	// Start point of new line of text
	int startPoint = x;

	Font* font = _resourcemanager.GetFont(text->fontPath, text->fontSize);
	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text->text.begin(); c != text->text.end(); c++) {
		//If enter char, start new line
		if (*c == '\n') {
			enterCounter++;
			x = startPoint;
			continue;
		}
		//Get character from font
		Character ch = font->Characters[*c];
		//Set position
		GLfloat xpos = x + ch.Bearing.x;
		GLfloat ypos = y - ch.Bearing.y + enterCounter * text->fontSize;
		//Get witch and height
		GLfloat w = ch.Size.x;
		GLfloat h = ch.Size.y;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
		{xpos,     ypos,       0.0, 0.0},
		{xpos,     ypos + h,   0.0, 1.0},
		{xpos + w, ypos + h,   1.0, 1.0},

		{xpos + w, ypos + h,   1.0, 1.0},
		{xpos + w, ypos,       1.0, 0.0},
		{xpos,     ypos,       0.0, 0.0}

		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, _textVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6); // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::RenderBasicShape(glm::mat4 modelMatrix, BasicShapes* basicShape) {
	Shader* shader = _resourcemanager.GetShader(basicShape->Vertexshader().c_str(), basicShape->Fragmentshader().c_str());
	shader->Use();

	Mesh* mesh = _resourcemanager.GetMesh(basicShape->size.x, basicShape->size.y, basicShape->pivot.x, basicShape->pivot.y, basicShape->uvdim.x, basicShape->uvdim.y, basicShape->segments);

	RGBAColor color = basicShape->color;

	glBindVertexArray(_spriteVAO);
	RenderMesh(modelMatrix, shader, mesh, GL_TRIANGLES, color);
	glBindVertexArray(0);
}

void Renderer::RenderMesh(const glm::mat4 modelMatrix, Shader* shader, Mesh* mesh, GLuint mode, RGBAColor blendcolor) {
	glm::mat4 MVP = _projectionMatrix * _viewMatrix * modelMatrix; // Create MVP matrix

	shader->SetMat4("MVP", MVP); // Send transformation to the currently bound shader

	shader->SetInt("texture", 0); // Set the "texture" sampler to user Texture Unit 0

	shader->SetVec4("blendColor", (float)blendcolor.r / 255.0f, (float)blendcolor.g / 255.0f, (float)blendcolor.b / 255.0f, (float)blendcolor.a / 255.0f);

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
