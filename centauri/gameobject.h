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

	// Sprite
	Sprite* sprite() { return _sprite; };
	void addSprite(Sprite* spr);
	void deleteSprite();

	// Transform
	Point3 position;
	Point3 rotation;
	Point3 scale;

private:
	// Parent and child
	GameObject* _parent;
	std::vector<GameObject*> _children;

	// Sprite
	Sprite* _sprite;

};

#endif
