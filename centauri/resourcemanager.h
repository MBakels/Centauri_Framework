#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>
#include <string>
#include <map>

#include "config.h"
#include "shader.h"
#include "texture.h"
#include "mesh.h"

class ResourceManager {
public:
	ResourceManager();
	virtual ~ResourceManager();

	Shader* GetShader(const std::string& vs, const std::string& fs);
	Texture* GetTexture(const std::string& filename, int filter, int wrap);
	Mesh* GetSpriteMesh(int width, int height, float pivotx, float pivoty, float uvwidth, float uvheight);

private:
	std::map<std::string, Shader*> _shaders;
	std::map<std::string, Texture*> _textures;
	std::map<std::string, Mesh*> _meshes;

	void DeleteShader(const std::string& shadername);
	void DeleteTexture(const std::string& filename);
	void DeleteMesh(const std::string& meshname);


};

#endif
