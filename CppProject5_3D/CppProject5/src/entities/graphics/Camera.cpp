#include "GLM\glm.hpp"

#include "Camera.h"
#include "input\InputController.h"
#include "utils\maths\Maths.h"
#include "gameEngine\Configs.h"
#include "world\Map.h"


Camera::Camera(float x, float y, float z, float fpitch, float fyaw, float moveSpeed, float mouseSens)
	: position(glm::vec3(x, y, z)), pitch(fpitch), yaw(fyaw), movementSpeed(moveSpeed), mouseSensitivity(mouseSens), worldUp(Configs::CAM_BASE_WORLD_UP), front(Configs::CAM_BASE_FRONT) {
	processMouseMovement(0, 0, false);
}

Camera::Camera(float x, float y, float z)
	: Camera(x, y, z, 0.0f, Configs::CAM_BASE_YAW, Configs::BASE_MOVE_SPEED, Configs::BASE_MOUSE_SENS) {
}

Camera::Camera(float x, float y, float z, float pitch, float yaw)
	: Camera(x, y, z, pitch, yaw, Configs::BASE_MOVE_SPEED, Configs::BASE_MOUSE_SENS) {
}

Camera::Camera()
	: Camera(0.0f, 0.0f, 0.0f, 0.0f, Configs::CAM_BASE_YAW, Configs::BASE_MOVE_SPEED, Configs::BASE_MOUSE_SENS){
}

Camera::~Camera() {

}

void Camera::updateCameraVectors() {
	// Calculate the front vector
	glm::vec3 frontv3;
	frontv3.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	frontv3.y = sin(glm::radians(pitch));
	frontv3.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(frontv3);
	// Calculate the right and up vectirs
	right = glm::normalize(glm::cross(front, worldUp));  
	up = glm::normalize(glm::cross(right, front));
}

void Camera::processKeyboard(CameraDirection direction, float deltaTime){
	float velocity = movementSpeed * deltaTime;

	if (direction == FORWARD) {
		position += front * velocity;
	}

	if (direction == BACKWARD) {
		position -= front * velocity;
	}

	if (direction == LEFT) {
		position -= right * velocity;
	}

	if (direction == RIGHT) {
		position += right * velocity;
	}

	if (direction == UP) {
		position += up * velocity;
	}

	if (direction == DOWN) {
		position -= up * velocity;
	}
}

void Camera::processMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch) {
	// offSets are scaled with the mouse sensitivity
	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;

	// variates the rotation angles
	yaw += xOffset;
	pitch += yOffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch) {
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Eular angles
	updateCameraVectors();
}

void Camera::move(float dx, float dy, float dz) {
	position += glm::vec3(dx, dy, dz);
}

void Camera::rotate(float dPitch, float dYaw) {
	pitch += dPitch;
	yaw += dYaw;
}

glm::vec3 Camera::getPosition() const {
	return position;
}

void Camera::setPosition(float fx, float fy, float fz) {
	position = glm::vec3(fx, fy, fz);
}

/* --- Getters --- */

// Uses glm::lookAt to get the viewMatrix
glm::mat4 Camera::getViewMatrix() const {
	return glm::lookAt(position, position + front, up);
}

float Camera::getX() const { return position.x; }
float Camera::getY() const { return position.y; }
float Camera::getZ() const { return position.z; }
float Camera::getPitch() const { return pitch; }
float Camera::getYaw() const { return yaw; }

