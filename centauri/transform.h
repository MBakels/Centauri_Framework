#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vector>

#include "vectorx.h"

class GameObject;

class Transform {

#define PROPERTY(t,n)  __declspec( property (put = property__set_##n, get = property__get_##n)) t n; \
	typedef t property__tmp_type_##n
#define READONLY_PROPERTY(t,n) __declspec( property (get = property__get_##n) ) t n; \
	typedef const t property__tmp_type_##n
#define WRITEONLY_PROPERTY(t,n) __declspec( property (put = property__set_##n) ) t n; \
	typedef t property__tmp_type_##n
#define GET(n) property__tmp_type_##n property__get_##n()
#define SET(n) property__tmp_type_##n property__set_##n(const property__tmp_type_##n& value)

public:
	Transform(GameObject* gameObject);

	virtual ~Transform();

	// Position of GameObject in worldspace
	PROPERTY(Point3, position);
	GET(position) {
		return _position;
	}
	SET(position) {
		//_position = value;
		_localPosition = value - _parent->position;
		UpdateTransforms();
		return _position;
	}

	// Rotation of GameObject in worldspace
	PROPERTY(Point3, rotation);
	GET(rotation) {
		return _rotation;
	}
	SET(rotation) {
		//_rotation = value;
		_localRotation = value - _parent->rotation;
		UpdateTransforms();
		return _rotation;
	}

	// Scale of GameObject in worldspace
	PROPERTY(Point3, scale);
	GET(scale) {
		return _scale;
	}
	SET(scale) {
		//_scale = value;
		_localScale = value - _parent->scale;
		UpdateTransforms();
		return _scale;
	}

	// Position of GameObject in localspace
	PROPERTY(Point3, localPosition);
	GET(localPosition) {
		return _localPosition;
	}
	SET(localPosition) {
		_localPosition = value;
		//_position = _localPosition + _parent->position;
		UpdateTransforms();
		return _localPosition;
	}

	// Rotation of GameObject in localspace
	PROPERTY(Point3, localRotation);
	GET(localRotation) {
		return _localRotation;
	}
	SET(localRotation) {
		_localRotation = value;
		//_rotation = _localRotation + _parent->rotation;
		UpdateTransforms();
		return _localRotation;
	}

	// Scale of GameObject in localspace
	PROPERTY(Point3, localScale);
	GET(localScale) {
		return _localScale;
	}
	SET(localScale) {
		_localScale = value;
		//_scale = _localScale + _parent->scale;
		UpdateTransforms();
		return _localScale;
	}

	// Update the world-relative propertys of this transform and all child transforms
	void UpdateTransforms();

	// Children
	void AddChild(Transform* child);
	void RemoveChild(Transform* child);
	Transform* GetChild(unsigned int i);
	const std::vector<Transform*>& Children() { return _children; };

private:
	// The GameObject this Transform is attached to
	GameObject* gameObject;

	// Worldspace
	Point3 _position;
	Point3 _rotation;
	Point3 _scale;

	// Localspace
	Point3 _localPosition;
	Point3 _localRotation;
	Point3 _localScale;

	// Parent and children
	Transform* _parent;
	std::vector<Transform*> _children;

};

#endif
