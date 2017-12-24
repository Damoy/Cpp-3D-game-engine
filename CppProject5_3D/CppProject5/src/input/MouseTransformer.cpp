#include "MouseTransformer.h"
#include "InputController.h"


glm::vec3 MouseTransformer::VEC_NULL = glm::vec3(-42, -42, -42);

// To normalized space
glm::vec3 MouseTransformer::getNormalizedCoords(float mouseX, float mouseY) {
	float x = ((2.0f * mouseX) / Configs::WIDTH) - 1.0f;
	float y = 1.0f - (2.0f * mouseY) / Configs::HEIGHT;
	float z = 1.0f;
	return glm::vec3(x, y, z);
}

// To Homogeneous clip space
glm::vec4 MouseTransformer::getHomogeneousCoords(glm::vec3 normalizedCoords) {
	return glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
}

// To eye space
glm::vec4 MouseTransformer::getEyeCoords(glm::mat4 projMatrix, glm::vec4 homogCoords) {
	glm::vec4 rayEye = glm::inverse(projMatrix) * homogCoords;
	return glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);
}

// To world space
glm::vec4 MouseTransformer::getWorldCoords(glm::mat4 viewMatrix, glm::vec4 eyeCoords) {
	glm::vec4 rayWorld = (glm::inverse(viewMatrix) * eyeCoords);
	// normalizing the vector
	return glm::normalize(rayWorld);
}

// From viewport space to world space !
glm::vec3 MouseTransformer::toWorldCoords(float mouseX, float mouseY, glm::mat4 projMatrix, glm::mat4 viewMatrix) {
	// normalize space
	glm::vec3 normalizedCoords = getNormalizedCoords(mouseX, mouseY);
	// homogeneous space
	glm::vec4 homogCoords = getHomogeneousCoords(normalizedCoords);
	// eye space
	glm::vec4 eyeCoords = getEyeCoords(projMatrix, homogCoords);
	// world space
	glm::vec4 worldCoords = getWorldCoords(viewMatrix, eyeCoords);
	// get first 3 coords
	glm::vec3 worldCoords3D = glm::vec3(worldCoords.x, worldCoords.y, worldCoords.z);
	return worldCoords3D;
}

glm::vec3 MouseTransformer::toWorldCoords(glm::vec2 mousePos, glm::mat4 projMatrix, glm::mat4 viewMatrix) {
	return toWorldCoords(mousePos.x, mousePos.y, projMatrix, viewMatrix);
}

// >>> GET THE MOUSE LEVEL COLLISION POINT <<<
glm::vec3 MouseTransformer::getCollisionPointOnLevelMap(Level* level, Camera* camera, glm::mat4 projectionMatrix) {
	// get the view matrix
	glm::mat4 viewMatrix = camera->getViewMatrix();

	// the viewport mouse coordinates
	glm::vec2 mousePos = InputController::getMousePosition();
	// get the mouse rayy
	glm::vec3 mouseRay = MouseTransformer::toWorldCoords(mousePos, projectionMatrix, viewMatrix);

	// up normal
	glm::vec3 planeNormal = glm::vec3(0.0f, 1.0f, 0.0f);
	// dot product between the normal and the mouse ray
	float denom = glm::dot(planeNormal, mouseRay);

	Map* levelMap = level->getMap();

	float centerX = (level->getX() + level->getWidth()) / 2.0f;
	float centerY = 0.0f;
	float centerZ = (level->getZ() + level->getWidth()) / 2.0f;

	// centered coords
	glm::vec3 center = glm::vec3(centerX, centerY, centerZ);
	// camera origin
	glm::vec3 origin = camera->getPosition();

	if (glm::abs(denom) > 0.0001f) {
		// center to player direction
		glm::vec3 centerPlay = glm::vec3(center.x - origin.x, center.y - origin.y, center.z - origin.z);
		// to check if there is indeed level collision
		float t = glm::dot(centerPlay, planeNormal) / denom;

		// if there is
		if (t >= 0) {
			// scale the mouse ray
			glm::vec3 mouseRayT = glm::vec3(mouseRay.x * t, mouseRay.y * t, mouseRay.z * t);
			// the collision point is the camera origin plus the scaled mouse ray
			glm::vec3 collisionPoint = origin + mouseRayT;

			return collisionPoint;
		}
	}

	return VEC_NULL;
}

bool MouseTransformer::isNull(glm::vec3 vec) {
	return (vec.x == VEC_NULL.x && vec.y == VEC_NULL.y && vec.z == VEC_NULL.z);
}

