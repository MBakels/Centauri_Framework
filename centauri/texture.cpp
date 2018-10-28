#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "texture.h"

Texture::Texture() {
	_width = 0;
	_height = 0;
	_bitdepth = 3;

	_gltexture = 0;
	stbi_set_flip_vertically_on_load(true);
}

Texture::~Texture() {
	glDeleteTextures(1, &_gltexture);
}

GLuint Texture::LoadImageFromDisk(const std::string& imagepath , int filter, int wrap) {
	// Debug text
	std::cout << "Loading Image: " << imagepath << std::endl;

	// Load the image using stb_image
	unsigned char *data = stbi_load(imagepath.c_str(), &_width, &_height, &_bitdepth, 0);
	if(data == NULL) {
		std::cout << "ERROR::TEXTURE::LOADFILE::UNABLE_TO_LOAD_FILE" << std::endl;
		return 0;
	}

	// Creating a OpenGL texture and binding it
	glGenTextures(1, &_gltexture);
	glBindTexture(GL_TEXTURE_2D, _gltexture);

	// filter the Texture
	switch (filter) {
	case 0:
		// No filtering (Nearest-neighbour)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	case 1:
		// Bilinear filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case 2:
		// Bilinear mipmap filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);		
		break;
	case 3:
		// Trilinear filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	default:
		// No filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	}

	// wrap the Texture
	if (wrap == 0) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	} else if (wrap == 1) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	} else if (wrap == 2) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	// handle transparency and grayscale and give the image to OpenGL
	switch (_bitdepth) {
	case 4:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		break;
	case 3:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		break;
	case 1:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, _width, _height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
		break;
	default:
		std::cout << "ERROR::TEXTURE::BITDEPTH::BITDEPTH_NOT_1_3_OR_4" << std::endl;
		break;
	}

	// GenerateMipmap if Bilinear or Trilinear filter is enabled
	if (filter == 2 || filter == 3) {
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	// Freeing data as OpenGL copied it
	stbi_image_free(data);

	// Returning ID of texture
	return _gltexture;
}