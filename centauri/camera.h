#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/euler_angles.hpp>
#include "config.h"

class Camera {
public:
	Camera();
	virtual ~Camera();

	glm::vec3 position;
	glm::vec3 rotation;

	void UpdateCamera();
	glm::mat4 GetViewMatrix() { return _viewMatrix; };
	glm::mat4 GetProjectionMatrix() { return _projectionMatrix; };

	void Camera::orthogonal();

private:
	glm::mat4 _viewMatrix;
	glm::mat4 _projectionMatrix;

	glm::vec3 _offset;

	glm::vec3 _up;
	glm::vec3 _right;
	glm::vec3 _direction;
};

#endif
