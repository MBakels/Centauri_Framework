#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "vectorx.h"

class Camera {
public:
	Camera();
	virtual ~Camera();

	void updateCamera();

	glm::mat4 viewMatrix() { return _viewMatrix; };
	glm::mat4 projectionMatrix() { return _projectionMatrix; };

	void Camera::orthogonal();

	Point3 position;
	Point3 rotation;

private:
	glm::mat4 _viewMatrix;
	glm::mat4 _projectionMatrix;

	glm::vec3 _up;
	glm::vec3 _right;
	glm::vec3 _direction;
};

#endif
