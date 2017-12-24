#pragma once

#include "GLM\glm.hpp"
#include "utils\colors\Color.h"

/*
	The light class.
	A light has a position and a color.
	Only one light (the "sun") is used in the project.
*/
class Light{
private:
	glm::vec3 position;
	Color* color;

public:
	Light(float x, float y, float z, float r, float g, float b);
	~Light();

	// getters
	float getX() const;
	float getY() const;
	float getZ() const;
	glm::vec3 getPosition() const;
	Color* getColor() const;

	// setters
	void setX(float x);
	void setY(float y);
	void setZ(float z);
};

