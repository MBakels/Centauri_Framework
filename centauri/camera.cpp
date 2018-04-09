#include "camera.h"
#include "config.h"

Camera::Camera() {
	position = Point3(0, 0, 5);
	rotation = Point3(0, PI, 0);

	_direction = glm::vec3(0, 0, -5);
	_up = glm::vec3(0, 1, 0);
	_right = glm::vec3(1, 0, 0);

	Orthogonal();
}

Camera::~Camera() {

}

void Camera::Orthogonal() {
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

	// View matrix
	_viewMatrix = glm::lookAt(pos, pos + _direction, _up);
}
