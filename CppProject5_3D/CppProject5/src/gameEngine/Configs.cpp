#include "Configs.h"

/*
Game configuration namespace.
Is used to change game behavior without
having to cross code.

*/
namespace Configs {
	// camera related
	// camera move speed and mouse sensitivity
	const float BASE_MOVE_SPEED = 2.0f; // was 2.5f
	const float BASE_MOUSE_SENS = 0.15f; // was 0.2f

	// camera vectors
	const glm::vec3 CAM_BASE_WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);
	const glm::vec3 CAM_BASE_FRONT = glm::vec3(0.0f, 0.0f, -1.0f);
	// camera angle
	const float CAM_BASE_YAW = 90.0f;

	// camera settings
	const float FOV = 70.0f; // was 45.0f
	const float NEAR_PLANE = 0.1f;
	const float FAR_PLANE = 1000.0f;
	const float ASPECT_RATIO = static_cast<float>(WIDTH) / static_cast<float>(HEIGHT);

	// the main camera
	Camera MAIN_CAMERA(-5.0f, 4.0f, -5.0f, -22.5f, 45.0f);

	// sample tower related
	// armor, life...
	const short SAMPLE_TOWER_ARMOR = 2;
	const short SAMPLE_TOWER_LIFE = 10;
	const short SAMPLE_TOWER_DAMAGE = 2;
	const float SAMPLE_TOWER_SIZE = 0.5f;
	const float SAMPLE_PROJECTILE_SIZE = 0.1f;
	const unsigned int SAMPLE_TOWER_PRICE = 10;
	const unsigned int ASTEROID_KILLED_BY_SAMPLED_GAIN = 6;

	// intelligent tower related
	const short INTELLIGENT_TOWER_ARMOR = 1;
	const short INTELLIGENT_TOWER_LIFE = 10;
	const short INTELLIGENT_TOWER_DAMAGE = 4;
	const float INTELLIGENT_TOWER_SIZE = 0.5f; // TODO see
	const float INTELLIGENT_PROJECTILE_SIZE = SAMPLE_PROJECTILE_SIZE;
	const unsigned int INTELLIGENT_TOWER_PRICE = 20; // todo balancing ?
	const unsigned int ASTEROID_KILLED_BY_INTELLIGENT_GAIN = 7;

	// asteroids related
	const float SAMPLE_ASTEROID_SIZE = 0.25f; // 0.5f

	// window related
	const unsigned short WIDTH = 1600; // 800 // 1024
	const unsigned short HEIGHT = 900; // 600 // 720
	const unsigned short UPS = 60; // 120 // unused
	char* TITLE = "Suicide project";

	// map related
	const float BASE_MAP_HEIGHT = 0.0f;

	// rendering related
	float SKY_RED_COMP = 0.1f;
	float SKY_GREEN_COMP = 0.1f;
	float SKY_BLUE_COMP = 0.1f;
	float SKY_ALPHA_COMP = 1.0f;

	// the only light used (can see its action on entities)
	Light SUN(0.0f, 10000.0f, -7000.0f, 1.0f, 1.0f, 1.0f);
	// should be used to activate certain opengl textures (GL_TEXTURE0, GL_TEXTURE1...)
	unsigned short MODEL_TEXTURE_ATLAS = 0;
	unsigned short GUI_TEXTURE_ATLAS = 1;

	// rotation related
	float ROT_45_RAD = glm::radians(45.0f);

	// levels related
	// world-relative position, sizes..
	float LEVEL1_X = 0.0f;
	float LEVEL1_Y = 0.0f;
	float LEVEL1_Z = 0.0f;
	float LEVEL1_WIDTH = 10.0f;
	float LEVEL1_HEIGHT = 10.0f;
	unsigned short LEVEL1_MAP_VERTICES_COUNT = 64;
	unsigned short LEVEL1_ENEMIES_STOCK = 60;

	float LEVEL2_X = 0.0f;
	float LEVEL2_Y = 0.0f;
	float LEVEL2_Z = 0.0f;
	float LEVEL2_WIDTH = 20.0f;
	float LEVEL2_HEIGHT = 20.0f;
	unsigned short LEVEL2_MAP_VERTICES_COUNT = 64;
	unsigned short LEVEL2_ENEMIES_STOCK = 80;
	unsigned short LEVEL2_MONEY_BONUS = 40;

	// player related
	const unsigned int PLAYER_BASE_MONEY = 40;

	// spawn related
	const float SPAWN_SIZE = 2.0f;
	// amount of asteroids to collide the level box before game over
	const unsigned short LEVEL1_MAX_ASTEROIDS_BEFORE_DEATH = 20;
	const unsigned short LEVEL2_MAX_ASTEROIDS_BEFORE_DEATH = 40;
}