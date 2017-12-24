#include "Maths.h"
#include "entities\Entity.h"

namespace Maths {
	glm::mat4 generateTransformationMatrix4f(float x, float y, float xScale, float yScale){
		glm::mat4 matrix(1.0f);
		glm::translate(matrix, glm::vec3(x, y, 1.0f));
		glm::scale(matrix, glm::vec3(xScale, yScale, 1.0f));
		return matrix;
	}

	glm::mat4 generateTransformationMatrix4f(glm::vec2 position, glm::vec2 scale) {
		return generateTransformationMatrix4f(position.x, position.y, scale.x, scale.y);
	}

	glm::mat4 generateTransformationMatrix4f(float x, float y, float z, float rx, float ry, float rz, float scale) {
		glm::mat4 matrix(1.0f);
		glm::vec3 position(x, y, z);

		// position
		matrix = glm::translate(matrix, position);
		// rotations
		matrix = glm::rotate(matrix, glm::radians(rx), glm::vec3(1.0f, 0.0f, 0.0f));
		matrix = glm::rotate(matrix, glm::radians(ry), glm::vec3(0.0f, 1.0f, 0.0f));
		matrix = glm::rotate(matrix, glm::radians(rz), glm::vec3(0.0f, 0.0f, 1.0f));
		// scaling
		matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));
		return matrix;
	}

	glm::mat4 generateTransformationMatrix4f(glm::vec3 position, float rx, float ry, float rz, float scale) {
		glm::mat4 matrix(1.0f);
		matrix = glm::translate(matrix, position);
		matrix = glm::rotate(matrix, glm::radians(rx), glm::vec3(1.0f, 0.0f, 0.0f));
		matrix = glm::rotate(matrix, glm::radians(ry), glm::vec3(0.0f, 1.0f, 0.0f));
		matrix = glm::rotate(matrix, glm::radians(rz), glm::vec3(0.0f, 0.0f, 1.0f));
		matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));
		return matrix;
	}

	glm::mat4 generateTransformationMatrix4f(glm::vec3 position, float rx, float ry, float rz, float xScale, float yScale, float zScale) {
		glm::mat4 matrix(1.0f);
		matrix = glm::translate(matrix, position);
		matrix = glm::rotate(matrix, glm::radians(rx), glm::vec3(1.0f, 0.0f, 0.0f));
		matrix = glm::rotate(matrix, glm::radians(ry), glm::vec3(0.0f, 1.0f, 0.0f));
		matrix = glm::rotate(matrix, glm::radians(rz), glm::vec3(0.0f, 0.0f, 1.0f));
		matrix = glm::scale(matrix, glm::vec3(xScale, yScale, zScale));
		return matrix;
	}

	glm::mat4 generateTransformationMatrix4f(glm::vec3 position, glm::vec3 rotation, float scale) {
		return generateTransformationMatrix4f(position, rotation.x, rotation.y, rotation.z, scale);
	}
	
	glm::mat4 generateTransformationMatrix4f(glm::vec3 position, glm::vec3 rotation, float xScale, float yScale, float zScale) {
		return generateTransformationMatrix4f(position, rotation.x, rotation.y, rotation.z, xScale, yScale, zScale);
	}


	glm::mat4 generateViewMatrix(float x, float y, float z, float pitch, float yaw) {
		// pitch rotation
		glm::mat4 viewMatrix = glm::rotate(glm::mat4(1.0f), pitch, glm::vec3(1.0f, 0.0f, 0.0f));
		// yaw rotation
		viewMatrix = glm::rotate(viewMatrix, yaw, glm::vec3(0.0f, 1.0f, 0.0f));
		// position
		viewMatrix = glm::translate(viewMatrix, glm::vec3(-x, -y, -z));
		return viewMatrix;
	}

	glm::mat4 generateProjectionMatrix(float FOVdegrees, float aspectRatio, float nearPlane, float farPlane) {
		return glm::perspective(glm::radians(FOVdegrees), aspectRatio, nearPlane, farPlane);
	}

	inline float frand(float min, float max) {
		assert(max > min);
		float r = ((float)rand()) / (float)RAND_MAX;
		float diff = max - min;
		return (r * diff) + min;
	}

	inline int irand(int min, int max) {
		return min + (rand() % static_cast<int>(max - min + 1));
	}

	inline float min(float x1, float x2) {
		return (x1 > x2) ? x2 : x1;
	}

	inline float max(float x1, float x2) {
		return (x1 < x2) ? x2 : x1;
	}

	inline int abs(int x) {
		return x < 0 ? -x : x;
	}
}