#pragma once

#include "Asteroid.h"
#include "GLM\glm.hpp"

/*
	Actually, the only asteroid implemented on the game.
	As the model is took in the constructor, two SampleAsteroids could
	have different models but should not.
*/
class SampleAsteroid : public Asteroid{
public:
	SampleAsteroid(TexturedModel* model, glm::vec3 dest, float x, float y, float z, float scale);
	~SampleAsteroid();

	void update();
};

