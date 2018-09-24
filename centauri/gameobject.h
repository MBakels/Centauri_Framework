#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

#include "sprite.h"
#include "basicshapes.h"
#include "vectorx.h"
#include "input.h"
#include "singleton.h"

#include <ft2build.h>
#include FT_FREETYPE_H 

class GameObject {
public:
	GameObject();
	virtual ~GameObject();

	virtual void Update(float deltaTime);

	// Children
	void AddChild(GameObject* child);
	void RemoveChild(GameObject* child);
	GameObject* GetChild(unsigned int i);
	const std::vector<GameObject*>& Children() { return _children; };

	// Return input
	Input* GetInput() { return _input; };

	// Sprite
	Sprite* GetSprite() { return _sprite; };
	void AddSprite(const std::string& filename);
	void AddSprite(const std::string& filename, float pivotx, float pivoty);
	void AddSprite(const std::string& filename, float pivotx, float pivoty, float uvwidth, float uvheight);
	void AddSprite(const std::string& filename, float pivotx, float pivoty, float uvwidth, float uvheight, int filter, int wrap);
	void AddSpriteSheet(const std::string& filename, int horizontal, int vertical);
	void DeleteSprite();

	// Basic shapes
	BasicShapes* GetBasicShape() { return _basicShape; };
	BasicShapes* AddBasicShape();
	void DeleteBasicShape();

	// Transform
	Point3 position;
	Point3 rotation;
	Point3 scale;

private:
	// Parent and child
	GameObject* _parent;
	std::vector<GameObject*> _children;

	// Input
	Input* _input;

	// Sprite
	Sprite* _sprite;

	// Basic shape
	BasicShapes* _basicShape;

};

#endif
