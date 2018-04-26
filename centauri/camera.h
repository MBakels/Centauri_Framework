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

	void UpdateCamera();

	glm::mat4 ViewMatrix() { return _viewMatrix; };
	glm::mat4 ProjectionMatrix() { return _projectionMatrix; };

	void Camera::Orthogonal();

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
