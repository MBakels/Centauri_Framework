#include "gameobject.h"

GameObject::GameObject() {
	position = Point3(0.0f, 0.0f, 0.0f);
	rotation = Point3(0.0f, 0.0f, 0.0f);
	scale = Point3(1.0f, 1.0f, 1.0f);

	_parent = NULL;
	_sprite = NULL;

	_input = Singleton<Input>::instance();
}

GameObject::~GameObject() {

}

void GameObject::addChild(GameObject* child) {
	if (child->_parent != NULL) {
		child->_parent->removeChild(child);
	}
	child->_parent = this;
	this->_children.push_back(child);
}

void GameObject::removeChild(GameObject* child) {
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

GameObject* GameObject::getChild(unsigned int i) {
	if (i < _children.size()) {
		return _children[i];
	}
	return NULL;
}

void GameObject::addSprite(Sprite* spr) {
	deleteSprite();
	_sprite = new Sprite();
	*_sprite = *spr;
}

void GameObject::deleteSprite() {
	if (_sprite != NULL) {
		delete _sprite;
		_sprite = NULL;
	}
};