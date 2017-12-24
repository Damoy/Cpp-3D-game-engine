#include <iostream>
#include "SampleAsteroid.h"
#include "utils\maths\Maths.h"
#include "gameEngine\Configs.h"


SampleAsteroid::SampleAsteroid(TexturedModel* model, glm::vec3 dest, float x, float y, float z, float scale)
	: Asteroid(model, dest, x, y, z, scale, scale, scale, 1, 1, 0, 0.005f){
}

SampleAsteroid::~SampleAsteroid(){
}

void SampleAsteroid::update() {
	if (!isAlive())
		return;

	// super update
	Enemy::update();
	// check if the asteroid is dead
	checkState();

	// the updated asteroid direction
	glm::vec3 dir = dest - position;
	// the asteroid goes into its direction with a certain speed
	position += speed * dir;

	// rotate it..
	float rot = Configs::ROT_45_RAD;
	incRot(rot, rot, rot);
}