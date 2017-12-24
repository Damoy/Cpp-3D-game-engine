#pragma once

#include "GLM\glm.hpp"
#include "entities\graphics\Light.h"
#include "entities\graphics\Camera.h"

/*
	Game configuration namespace.
	Is used to change game behavior without
	having to cross code.

*/
namespace Configs {
	// camera related
	// camera move speed and mouse sensitivity
	extern const float BASE_MOVE_SPEED;
	extern const float BASE_MOUSE_SENS;

	// camera vectors
	extern const glm::vec3 CAM_BASE_WORLD_UP;
	extern const glm::vec3 CAM_BASE_FRONT;
	// camera angle
	extern const float CAM_BASE_YAW;

	// camera settings
	extern const float FOV;
	extern const float NEAR_PLANE;
	extern const float FAR_PLANE;
	extern const float ASPECT_RATIO;

	// the main camera
	extern Camera MAIN_CAMERA;

	// sample tower related
	// armor, life...
	extern const short SAMPLE_TOWER_ARMOR;
	extern const short SAMPLE_TOWER_LIFE;
	extern const short SAMPLE_TOWER_DAMAGE;
	extern const float SAMPLE_TOWER_SIZE;
	extern const float SAMPLE_PROJECTILE_SIZE;
	extern const unsigned int SAMPLE_TOWER_PRICE;
	extern const unsigned int ASTEROID_KILLED_BY_SAMPLED_GAIN;

	// intelligent tower related
	extern const short INTELLIGENT_TOWER_ARMOR;
	extern const short INTELLIGENT_TOWER_LIFE;
	extern const short INTELLIGENT_TOWER_DAMAGE;
	extern const float INTELLIGENT_TOWER_SIZE;
	extern const float INTELLIGENT_PROJECTILE_SIZE;
	extern const unsigned int INTELLIGENT_TOWER_PRICE;
	extern const unsigned int ASTEROID_KILLED_BY_INTELLIGENT_GAIN;

	// asteroids related
	extern const float SAMPLE_ASTEROID_SIZE;

	// window related
	extern const unsigned short WIDTH;
	extern const unsigned short HEIGHT;
	extern const unsigned short UPS;
	extern char* TITLE;

	// map related
	extern const float BASE_MAP_HEIGHT;

	// rendering related
	extern float SKY_RED_COMP;
	extern float SKY_GREEN_COMP;
	extern float SKY_BLUE_COMP;
	extern float SKY_ALPHA_COMP;

	// the only light used (can see its action on entities)
	extern Light SUN;
	// should be used to activate certain opengl textures (GL_TEXTURE0, GL_TEXTURE1...)
	extern unsigned short MODEL_TEXTURE_ATLAS;
	extern unsigned short GUI_TEXTURE_ATLAS;

	// rotation related
	extern float ROT_45_RAD;

	// levels related
	// world-relative position, sizes..
	extern float LEVEL1_X;
	extern float LEVEL1_Y;
	extern float LEVEL1_Z;
	extern float LEVEL1_WIDTH;
	extern float LEVEL1_HEIGHT;
	extern unsigned short LEVEL1_MAP_VERTICES_COUNT;
	extern unsigned short LEVEL1_ENEMIES_STOCK;

	extern float LEVEL2_X;
	extern float LEVEL2_Y;
	extern float LEVEL2_Z;
	extern float LEVEL2_WIDTH;
	extern float LEVEL2_HEIGHT;
	extern unsigned short LEVEL2_MAP_VERTICES_COUNT;
	extern unsigned short LEVEL2_ENEMIES_STOCK;
	extern unsigned short LEVEL2_MONEY_BONUS;

	// player related
	extern const unsigned int PLAYER_BASE_MONEY;

	// spawn related
	extern const float SPAWN_SIZE;
	// amount of asteroids to collide the level box before game over
	extern const unsigned short LEVEL1_MAX_ASTEROIDS_BEFORE_DEATH;
	extern const unsigned short LEVEL2_MAX_ASTEROIDS_BEFORE_DEATH;
}