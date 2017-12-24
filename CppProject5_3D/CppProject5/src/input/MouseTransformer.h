#pragma once

#include "entities\graphics\Camera.h"
#include "world\Level.h"

/*
	The Mouse Transformer is an important class.
	It allows to convert from simple 2D mouse coordinates to game-world ones.
	To do such, there are multiple conversions that need to be performed.
	Screen (viewport) Space -> Normalized Space -> Homogenous Clip Space -> Eye Space -> World Space (-> Local Space)
*/
class MouseTransformer{
private:
	MouseTransformer();

	// a tool vector
	static glm::vec3 VEC_NULL;
public:

	// transform from viewport space to normalized space
	static glm::vec3 getNormalizedCoords(float mouseX, float mouseY);
	// transform from normalized space to homogeneous clip space
	static glm::vec4 getHomogeneousCoords(glm::vec3 normCoords);
	// transform from homogeneous clip space to eye space
	static glm::vec4 getEyeCoords(glm::mat4 projMatrix, glm::vec4 homogCoords);
	// transform from eye space to world space
	static glm::vec4 getWorldCoords(glm::mat4 viewMatrix, glm::vec4 eyeCoords);

	// transform from viewport space to world space
	static glm::vec3 toWorldCoords(float mouseX, float mouseY, glm::mat4 projMatrix, glm::mat4 viewMatrix);
	// transform from viewport space to world spaceeeee
	static glm::vec3 toWorldCoords(glm::vec2 mousePos, glm::mat4 projMatrix, glm::mat4 viewMatrix);
	// >>> GET THE MOUSE LEVEL COLLISION POINT <<<
	// Yes, was though..
	static glm::vec3 getCollisionPointOnLevelMap(Level* level, Camera* camera, glm::mat4 projectionMatrix);
	// is the vector equals to the VEC_NULL one
	static bool isNull(glm::vec3);

};

