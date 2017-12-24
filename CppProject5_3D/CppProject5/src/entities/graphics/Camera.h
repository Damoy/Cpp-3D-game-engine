#pragma once

#include "GL\glew.h"
#include "GLM\glm.hpp"

/*
	The 3D camera.
	On the project, only one camera is used, which is the Player's one.
*/
class Camera{
private:

	// camera vectors for movement and rotation
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	// rotation attributes (Euler angles)
	float pitch;
	float yaw;
	// speed attributes
	float movementSpeed;
	float mouseSensitivity;
	float zoom;

	// Updates the camera vectors used for
	// the position, rotation and so the view matrix
	void updateCameraVectors();

public:

	// used for camera direction
	enum CameraDirection {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	Camera(float x, float y, float z, float pitch, float yaw, float moveSpeed, float mouseSens);
	Camera(float x, float y, float z, float pitch, float yaw);
	Camera(float x, float y, float z);
	Camera();
	~Camera();

	// Processes camera with keyboard input, deltaTime is used for variations
	void processKeyboard(CameraDirection direction, float deltaTime);
	// Processes camera with mouse movement.
	void processMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true);

	// Camera movement
	void move(float dx, float dy, float dz);
	// Rotate the camera, takes the pitch and yaw variations
	void rotate(float dPitch, float dYaw);
	void setPosition(float x, float y, float z);

	// getters
	float getX() const;
	float getY() const;
	float getZ() const;
	float getPitch() const;
	float getYaw() const;
	glm::vec3 getPosition() const;

	// generate a new view matrix
	glm::mat4 getViewMatrix() const;
};

