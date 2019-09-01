#include "transform.h"

Transform::Transform(GameObject* gameObject) {
	this->gameObject = gameObject;
}

Transform::~Transform() {
	gameObject = NULL;
}

void Transform::UpdateTransforms() {
	_position = _localPosition + _parent->position;
	_rotation = _localRotation + _parent->rotation;
	_scale = _localScale + _parent->scale;
	for each (Transform* transform in _children) {
		transform->UpdateTransforms();
	}
}
