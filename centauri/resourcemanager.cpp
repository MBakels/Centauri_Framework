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

	std::cout << "##### ResourceManager cleanup is done #####" << std::endl;
}

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
