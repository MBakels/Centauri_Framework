#include "resourcemanager.h"

ResourceManager::ResourceManager() {
	std::cout << "##### ResourceManager created #####" << std::endl;
}

ResourceManager::~ResourceManager() {
	std::cout << "##### ResourceManager cleanup start #####" << std::endl;

	std::cout << "----- Deleting shaders -----" << std::endl;
	std::map<std::string, Shader*>::iterator shader_it;
	for (shader_it = _shaders.begin(); shader_it != _shaders.end(); ++shader_it) {
		if (shader_it->second != NULL) {
			DeleteShader(shader_it->first);
		}
	}
	_shaders.clear();

	std::cout << "----- Deleting Textures -----" << std::endl;
	std::map<std::string, Texture*>::iterator texture_it;
	for (texture_it = _textures.begin(); texture_it != _textures.end(); ++texture_it) {
		if (texture_it->second != NULL) {
			DeleteTexture(texture_it->first);
		}
	}
	_textures.clear();

	std::cout << "----- Deleting Meshes -----" << std::endl;
	std::map<std::string, Mesh*>::iterator mesh_it;
	for (mesh_it = _meshes.begin(); mesh_it != _meshes.end(); ++mesh_it) {
		if (mesh_it->second != NULL) {
			DeleteMesh(mesh_it->first);
		}
	}
	_meshes.clear();

	std::cout << "----- Deleting Fonts -----" << std::endl;
	std::map<std::string, Font*>::iterator font_it;
	for (font_it = _fonts.begin(); font_it != _fonts.end(); ++font_it) {
		if (font_it->second != NULL) {
			DeleteFont(font_it->first);
		}
	}
	_fonts.clear();

	std::cout << "##### ResourceManager cleanup is done #####" << std::endl;
}

// Shaders
Shader* ResourceManager::GetShader(const std::string& vs, const std::string& fs) {
	std::string filename = vs + "_" + fs;
	if (_shaders[filename] != NULL) {
		return _shaders[filename];
	} else {
		Shader* shader = new Shader(vs.c_str(), fs.c_str());
		_shaders[filename] = shader;
		return shader;
	}
}

void ResourceManager::DeleteShader(const std::string& shadername) {
	delete _shaders[shadername];
	_shaders[shadername] = NULL;
}

// Textures
Texture* ResourceManager::GetTexture(const std::string& filePath, int filter, int wrap) {
	if (_textures[filePath] != NULL) {
		return _textures[filePath];
	} else {
		Texture* tex = new Texture();
		tex->LoadImageFromDisk(filePath, filter, wrap);
		_textures[filePath] = tex;
		return tex;
	}
}

void ResourceManager::DeleteTexture(const std::string& filename) {
	delete _textures[filename];
	_textures[filename] = NULL;
}

// Meshes
Mesh* ResourceManager::GetMesh(int width, int height, float pivotx, float pivoty, float uvwidth, float uvheight, int circleSegments) {
	char buf[64];
	sprintf(buf, "%dx%d_%.5fx%.5f_%.5fx%.5f_%d", width, height, pivotx, pivoty, uvwidth, uvheight, circleSegments);
	std::string meshname(buf);

	if (_meshes[meshname] != NULL) {
		return _meshes[meshname];
	} else {
		Mesh* m = new Mesh();
		if (circleSegments != 0) {
			m->GenerateCircleMesh(width / 2, circleSegments, pivotx, pivoty, uvwidth, uvheight);
		} else {
			m->GenerateSpriteMesh(width, height, pivotx, pivoty, uvwidth, uvheight);
		}
		_meshes[meshname] = m;
		return m;
	}
}

void ResourceManager::DeleteMesh(const std::string& meshname) {
	delete _meshes[meshname];
	_meshes[meshname] = NULL;
}

// Fonts
Font* ResourceManager::GetFont(const std::string& filePath, int fontSize) {
	std::string filename = filePath + "_" + std::to_string(fontSize);
	if (_fonts[filename] != NULL) {
		return _fonts[filename];
	} else {
		Font* font = new Font(filePath.c_str(), fontSize);
		_fonts[filename] = font;
		return font;
	}
}

void ResourceManager::DeleteFont(const std::string& fontname) {
	delete _fonts[fontname];
	_fonts[fontname] = NULL;
}