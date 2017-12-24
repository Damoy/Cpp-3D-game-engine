#pragma once

#include "GLM\glm.hpp"
#include "textures\ModelTexture.h"

/*
	The GUITexture class.
	A GUITexture should be a simple modeled texture to
	be use for user information.
*/
class GUITexture : public ModelTexture{
private:
	// the texture id
	unsigned int ID;
	// the screen position
	glm::vec2 position;
	// the texture scale
	glm::vec2 scale;

public:
	GUITexture(unsigned int ID, unsigned int width, unsigned int height, glm::vec2 position, glm::vec2 scale);
	~GUITexture();

	unsigned int getID() const;
	glm::vec2 getPosition() const;
	glm::vec2 getScale() const;
};

