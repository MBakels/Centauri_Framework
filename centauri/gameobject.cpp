#include "gameobject.h"

GameObject::GameObject() {
	position = Point3(0.0f, 0.0f, 0.0f);
	rotation = Point3(0.0f, 0.0f, 0.0f);
	scale = Point3(1.0f, 1.0f, 1.0f);

	_parent = NULL;
	_sprite = NULL;
	_basicShape = NULL;

	_input = Singleton<Input>::Instance();
}

GameObject::~GameObject() {
	DeleteSprite();
	DeleteBasicShape();
}

// Children
void GameObject::AddChild(GameObject* child) {
	if (child->_parent != NULL) {
		child->_parent->RemoveChild(child);
	}
	child->_parent = this;
	this->_children.push_back(child);
}

void GameObject::RemoveChild(GameObject* child) {
	std::vector< GameObject* >::iterator it = _children.begin();
	while (it != _children.end()) {
		if ((*it) == child) {
			child->_parent = NULL;
			it = _children.erase(it);
		} else {
			++it;
		}
	}
}

GameObject* GameObject::GetChild(unsigned int i) {
	if (i < _children.size()) {
		return _children[i];
	}
	return NULL;
}

// Sprites
void GameObject::AddSprite(const std::string& filename) {
	DeleteSprite();
	_sprite = new Sprite(filename);
}

void GameObject::AddSprite(const std::string& filename, float pivotx, float pivoty) {
	DeleteSprite();
	_sprite = new Sprite(filename, pivotx, pivoty);
}

void GameObject::AddSprite(const std::string& filename, float pivotx, float pivoty, float uvwidth, float uvheight) {
	DeleteSprite();
	_sprite = new Sprite(filename, pivotx, pivoty, uvwidth, uvheight);
}

void GameObject::AddSprite(const std::string& filename, float pivotx, float pivoty, float uvwidth, float uvheight, int filter, int wrap) {
	DeleteSprite();
	_sprite = new Sprite(filename, pivotx, pivoty, uvwidth, uvheight, filter, wrap);
}

void GameObject::DeleteSprite() {
	if (_sprite != NULL) {
		delete _sprite;
		_sprite = NULL;
	}
}

// Basic shapes
BasicShapes* GameObject::AddBasicShape() {
	DeleteBasicShape();
	_basicShape = new BasicShapes();
	return _basicShape;
}

void GameObject::DeleteBasicShape() {
	if (_basicShape != NULL) {
		delete _basicShape;
		_basicShape = NULL;
	}
}
