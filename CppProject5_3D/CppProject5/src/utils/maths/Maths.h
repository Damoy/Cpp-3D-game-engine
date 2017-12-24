#pragma once

#include "GLM\vec3.hpp"
#include "GLM\vec4.hpp"
#include "GLM\mat4x4.hpp"
#include "GLM\gtc\matrix_transform.hpp"

namespace Maths {
	/*
		Below are for transformation matrix generation.
		A transformation matrix is composed of the model position,
		rotation and scale
	*/

	extern glm::mat4 generateTransformationMatrix4f(float x, float y, float xScale, float yScale);
	extern glm::mat4 generateTransformationMatrix4f(glm::vec2 position, glm::vec2 scale);

	extern glm::mat4 generateTransformationMatrix4f(float x, float y, float z, float rx, float ry, float rz, float scale);

	extern glm::mat4 generateTransformationMatrix4f(glm::vec3 position, float rx, float ry, float rz, float xScale, float yScale, float zScale);
	extern glm::mat4 generateTransformationMatrix4f(glm::vec3 position, float rx, float ry, float rz, float scale);

	extern glm::mat4 generateTransformationMatrix4f(glm::vec3 position, glm::vec3 rotation, float xScale, float yScale, float zScale);
	extern glm::mat4 generateTransformationMatrix4f(glm::vec3 position, glm::vec3 rotation, float scale);


	// Generates a view matrix, given the position and eugler angles
	extern glm::mat4 generateViewMatrix(float x, float y, float z, float pitch, float yaw);

	// Generates a projection matrix given required parameters as the field of view, the aspect ratio (screen width / height),
	// the near plane and far plane
	// https://en.wikipedia.org/wiki/Viewing_frustum
	extern glm::mat4 generateProjectionMatrix(float FOVdegrees, float aspectRatio, float nearPlane, float farPlane);

	// float and int rand
	extern inline float frand(float min, float max);
	extern inline int irand(int min, int max);

	// simple min and max
	extern inline float min(float x1, float x2);
	extern inline float max(float x1, float x2);

}