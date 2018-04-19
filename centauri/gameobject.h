#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

#include "sprite.h"
#include "vectorx.h"
#include "input.h"
#include "singleton.h"

class GameObject {
public:
	GameObject();
	virtual ~GameObject();

	virtual void update(float deltaTime) {};

	// Children
	void addChild(GameObject* child);
	void removeChild(GameObject* child);
	GameObject* getChild(unsigned int i);
	const std::vector<GameObject*>& children() { return _children; };

	// Return input
	Input* input() { return _input; };

	// Sprite
	Sprite* sprite() { return _sprite; };
	void addSprite(Sprite* spr);
	void addSprite(const std::string& filename);
	void addSprite(const std::string& filename, float pivotx, float pivoty);
	void deleteSprite();

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

};

#endif
