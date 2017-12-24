#include "Asteroid.h"


Asteroid::Asteroid(TexturedModel* model, glm::vec3 d, float x, float y, float z, float xScale, float yScale, float zScale, unsigned short life, unsigned short dps, unsigned short arm, float s)
	:	Enemy(model, x, y, z, xScale, yScale, zScale, life, dps, arm),
		dest(d), speed(s){
}

Asteroid::~Asteroid(){
}

