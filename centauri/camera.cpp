#include "camera.h"

#define PI			3.1415926535897932384626433832795
#define HALF_PI		1.5707963267948966192313216916398
#define RAD_TO_DEG	57.295779513082320876798154814105

Camera::Camera() {
	position = glm::vec3(0, 0, 5);
	rotation = glm::vec3(0, PI, 0);

	_direction = glm::vec3(0, 0, -5);
	_up = glm::vec3(0, 1, 0);
	_right = glm::vec3(1, 0, 0);

	orthogonal();
}

Camera::~Camera() {

}

void Camera::orthogonal() {
	//_offset = glm::vec3(400, 300, 0);
	//position = glm::vec3(0, 0, 5) + _offset;
	_projectionMatrix = glm::ortho(0.0f, (float)SWIDTH, (float)SHEIGHT, 0.0f, 0.1f, 100.0f);
	glDisable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void Camera::UpdateCamera() {
	// Direction vector: Spherical coordinates to Cartesian coordinates conversion
	_direction = glm::vec3(cos(rotation.x) * sin(rotation.y), sin(rotation.x), cos(rotation.x) * cos(rotation.y));

	// Right vector
	_right = glm::vec3(sin(rotation.y - HALF_PI), 0, cos(rotation.y - HALF_PI));
	_right = glm::rotateZ(_right, rotation.z*(float)RAD_TO_DEG);

	// Up vector
	_up = glm::cross(_right, _direction);

	glm::vec3 pos = glm::vec3(position.x, position.y, position.z);
	//glm::vec3 offset = glm::vec3(_offset.x, _offset.y, _offset.z);

	// View matrix
	//_viewMatrix = glm::lookAt(pos - offset, pos - offset + _direction, _up);
	_viewMatrix = glm::lookAt(position, position + _direction, _up);
}
