#include "gameobject.h"

GameObject::GameObject() {
	position = Point3(0.0f, 0.0f, 0.0f);
	rotation = Point3(0.0f, 0.0f, 0.0f);
	scale = Point3(1.0f, 1.0f, 1.0f);

	_parent = NULL;
	_sprite = NULL;
	_text = NULL;
	_basicShape = NULL;

	_input = Singleton<Input>::Instance();
}

GameObject::~GameObject() {
	DeleteSprite();
	DeleteBasicShape();
	DeleteText();
}

void GameObject::Update() {
	if (_sprite != NULL) _sprite->Update();
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

void GameObject::AddSpriteSheet(const std::string& filename, int horizontal, int vertical) {
	DeleteSprite();
	float uvwidth = 1.0f / horizontal;
	float uvheight = 1.0f / vertical;
	_sprite = new Sprite(filename, 0.5f, 0.5f, uvwidth, uvheight);
	_sprite->Frame(0);
}

void GameObject::DeleteSprite() {
	if (_sprite != NULL) {
		delete _sprite;
		_sprite = NULL;
	}
}

// Text
void GameObject::AddText(std::string text, std::string fontPath, int fontSize, RGBAColor textColor) {
	DeleteText();
	_text = new Text(text, fontPath, fontSize, textColor);
}

void GameObject::DeleteText() {
	if (_text != NULL) {
		delete _text;
		_text = NULL;
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
