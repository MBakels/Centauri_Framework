#include <glad/glad.h>
#include "texture.h"

Texture::Texture() {
	_width = 0;
	_height = 0;
	_bitdepth = 3;

	_gltexture = 0;
}

Texture::~Texture() {
	glDeleteTextures(1, &_gltexture);
}

GLuint Texture::LoadTGA(const std::string& imagepath , int filter, int wrap) {
	std::cout << "Loading TGA: " << imagepath << std::endl;

	FILE *file;
	unsigned char type[4];
	unsigned char info[6];

#ifdef WIN32
	errno_t err;
	err = fopen_s(&file, imagepath.c_str(), "rb");
#else
	file = fopen(imagepath.c_str(), "rb");
#endif

	if (!file) {
		std::cout << "ERROR::TEXTURE::OPENFILE::UNABLE_TO_OPEN_FILE" << std::endl;
		return 0;
	}

	if (!fread(&type, sizeof(char), 3, file)) return 0;
	fseek(file, 12, SEEK_SET);
	if (!fread(&info, sizeof(char), 6, file)) return 0;

	//image type needs to be 2 (color) or 3 (grayscale)
	if (type[1] != 0 || (type[2] != 2 && type[2] != 3)) {
		std::cout << "ERROR::TEXTURE::IMAGETYPE::IMAGE_TYPE_NEITHER_COLOR_OR_GRAYSCALE" << std::endl;
		fclose(file);
		return 0;
	}

	unsigned char* data;

	_width = info[0] + info[1] * 256;
	_height = info[2] + info[3] * 256;
	_bitdepth = info[4] / 8;

	if (_bitdepth != 1 && _bitdepth != 3 && _bitdepth != 4) {
		std::cout << "ERROR::TEXTURE::BITDEPTH::BYTECOUNT_NOT_1_3_OR_4" << std::endl;
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

	unsigned int imagesize = _width * _height * _bitdepth;

	// Creating a buffer
	data = new unsigned char[imagesize];

	// Reading the actual data from the file into the buffer
	if (!fread(data, 1, imagesize, file)) return 0;

	// Everything is in memory now, closing file
	fclose(file);

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
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
		break;
	case 3:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
		break;
	case 1:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, _width, _height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
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
	delete[] data;

	// Returning ID of texture
	return _gltexture;
}