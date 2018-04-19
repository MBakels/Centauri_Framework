#include "config.h"
#include "sprite.h"

Sprite::Sprite() {
	
}

Sprite::Sprite(std::string image_path) {
	pivot = Point2(0.5f, 0.5f);
	uvdim = Point2(1.0f, 1.0f);
	uvoffset = Point2(0.0f, 0.0f);
	size = Point2(0, 0);

	_vertexshader = DEFAULTVERTEXSHADER;
	_fragmentshader = DEFAULTFRAGMENTSHADER;

	_filter = DEFAULTFILTER;
	_wrap = DEFAULTWRAP;

	// Load TGA file as texture
	_texture = loadTGA(image_path.c_str());

	// Vertex data
	GLfloat g_vertex_buffer_data[18] = {
		0.5f * size.x, -0.5f * size.y, 0.0f,
		-0.5f * size.x, -0.5f * size.y, 0.0f,
		-0.5f * size.x,  0.5f * size.y, 0.0f,

		-0.5f * size.x,  0.5f * size.y, 0.0f,
		0.5f * size.x,  0.5f * size.y, 0.0f,
		0.5f * size.x, -0.5f * size.y, 0.0f
	};

	// Two UV coordinates for each vertex.
	GLfloat g_uv_buffer_data[12] = {
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

	glGenBuffers(1, &_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &_uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
}


Sprite::~Sprite() {
	glDeleteBuffers(1, &_vertexbuffer);
	glDeleteBuffers(1, &_uvbuffer);
	glDeleteTextures(1, &_texture); // texture created in loadTGA() with glGenTextures()
}

GLuint Sprite::loadTGA(const std::string& imagepath) {
	std::cout << "Loading TGA: " << imagepath << std::endl;

	FILE *file;
	unsigned char type[4];
	unsigned char info[6];

	//file = fopen(imagepath.c_str(), "rb");

#ifdef WIN32
	errno_t err;
	err = fopen_s(&file, imagepath.c_str(), "rb");
#else
	file = fopen(imagepath.c_str(), "rb");
#endif

	if (!file) {
		std::cout << "ERROR::SPRITE::OPENFILE::UNABLE_TO_OPEN_FILE" << std::endl;
		return 0;
	}

	if (!fread(&type, sizeof(char), 3, file)) return 0;
	fseek(file, 12, SEEK_SET);
	if (!fread(&info, sizeof(char), 6, file)) return 0;

	//image type needs to be 2 (color) or 3 (grayscale)
	if (type[1] != 0 || (type[2] != 2 && type[2] != 3)) {
		std::cout << "ERROR::SPRITE::IMAGETYPE::IMAGE_TYPE_NEITHER_COLOR_OR_GRAYSCALE" << std::endl;
		fclose(file);
		return 0;
	}

	unsigned char* data;
	unsigned char bitdepth;

	size.x = info[0] + info[1] * 256;
	size.y = info[2] + info[3] * 256;
	bitdepth = info[4] / 8;

	if (bitdepth != 1 && bitdepth != 3 && bitdepth != 4) {
		std::cout << "ERROR::SPRITE::BITDEPTH::BYTECOUNT_NOT_1_3_OR_4" << std::endl;
		fclose(file);
		return 0;
	}

	/*
	// Check if the image's width and height is a power of 2. No biggie, we can handle it.
	if ((_width & (_width - 1)) != 0) {
		std::cout << "warning: " << imagepath << "’s width is not a power of 2" << std::endl;
	}
	if ((_height & (_height - 1)) != 0) {
		std::cout << "warning: " << imagepath << "’s height is not a power of 2" << std::endl;
	}
	if (_width != _height) {
		std::cout << "warning: " << imagepath << " is not square" << std::endl;
	}
	*/

	unsigned int imagesize = size.x * size.y * bitdepth;

	// Creating a buffer
	data = new unsigned char[imagesize];

	// Reading the actual data from the file into the buffer
	if (!fread(data, 1, imagesize, file)) return 0;

	// Everything is in memory now, closing file
	fclose(file);

	// Creating a OpenGL texture and binding it
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// filter the Texture
	switch (_filter) {
	case 0:
		// No filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		break;
	case 1:
		// Linear filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		break;
	case 2:
		// Bilinear filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		break;
	case 3:
		// Trilinear filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		break;
	default:
		// No filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		break;
	}

	// wrap the Texture
	if (_wrap == 0) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	} else if (_wrap == 1) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	} else if (_wrap == 2) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	// handle transparency and grayscale and give the image to OpenGL
	switch (bitdepth) {
	case 4:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
		break;
	case 3:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
		break;
	case 1:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, size.x, size.y, 0, GL_RED, GL_UNSIGNED_BYTE, data);
		_fragmentshader = DEFAULTGRAYSCALEFRAGMENTSHADER;
		break;
	default:
		std::cout << "ERROR::SPRITE::BITDEPTH::BITDEPTH_NOT_1_3_OR_4" << std::endl;
		break;
	}

	// Freeing data as OpenGL copied it
	delete[] data;

	// Returning ID of texture
	return textureID;
}
