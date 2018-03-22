#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>
#include <string>
#include <map>

#include "config.h"
#include "shader.h"

class ResourceManager {
public:
	ResourceManager();
	virtual ~ResourceManager();

	Shader* getShader(const std::string& vs, const std::string& fs);

private:
	std::map<std::string, Shader*> _shaders;

	void deleteShader(const std::string& shadername);
};

#endif // !RESOURCEMANAGER_H
