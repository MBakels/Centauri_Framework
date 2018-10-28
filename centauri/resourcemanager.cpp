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

	std::cout << "----- Delete Textures -----" << std::endl;
	std::map<std::string, Texture*>::iterator text_it;
	for (text_it = _textures.begin(); text_it != _textures.end(); ++text_it) {
		if (text_it->second != NULL) {
			DeleteTexture(text_it->first);
		}
	}
	_textures.clear();

	std::cout << "----- Delete Meshes -----" << std::endl;
	std::map<std::string, Mesh*>::iterator mesh_it;
	for (mesh_it = _meshes.begin(); mesh_it != _meshes.end(); ++mesh_it) {
		if (mesh_it->second != NULL) {
			DeleteMesh(mesh_it->first);
		}
	}
	_meshes.clear();

	std::cout << "##### ResourceManager cleanup is done #####" << std::endl;
}

// Shaders
Shader* ResourceManager::GetShader(const std::string& vs, const std::string& fs) {
	std::string filename;
	filename = vs;
	std::string tmp("_");
	filename.append(tmp);
	filename.append(fs);
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
Texture* ResourceManager::GetTexture(const std::string& filename, int filter, int wrap) {
	if (_textures[filename] != NULL) {
		return _textures[filename];
	} else {
		Texture* tex = new Texture();
		tex->LoadImageFromDisk(filename, filter, wrap);
		_textures[filename] = tex;
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