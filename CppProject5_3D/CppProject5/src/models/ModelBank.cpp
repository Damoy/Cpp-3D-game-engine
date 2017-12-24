#include "ModelBank.h"
#include "loaders\ModelLoader.h"
#include "gameEngine\Configs.h"

namespace ModelBank {

	namespace Textures {
		const char* GREEN_TEXTURE_128x128 = "res/textures/green_128x128.png";
		const char* GREEN_TEXTURE_16x16 = "res/textures/green_16x16.png";
		const char* GLASS_TEXTURE_64x64 = "res/textures/glass_64x64.png";
		const char* GRASS_TEXTURE_64x64 = "res/textures/grassGround_64x64.png";
		const char* GROUND_TEXTURE_64x64 = "res/textures/ground_64x64.png";
		const char* SPACE_TEXTURE_512x512 = "res/textures/bg_512x512.png";
		const char* GROUND_TEXTURE_128x128 = "res/textures/groundTexTest_128x128.png";
		const char* SELECT_TEXTURE_128x128 = "res/textures/select_128x128.png";

		const char* SAMPLE_ASTEROID_TEXTURE_128x128 = "res/textures/asteroid1_128x128.png";
		const char* SAMPLE_TOWER_TEXTURE_128x128 = "res/textures/sampleTower_128x128.png";
		const char* SAMPLE_PROJECTILE_TEXTURE_128x128 = SAMPLE_TOWER_TEXTURE_128x128;
		const char* SAMPLE_MAP_TEXTURE_128x128 = GREEN_TEXTURE_128x128;

		const char* INTELLIGENT_TOWER_TEXTURE_128x128 = "res/textures/intelligentTower2_128x128.png";
		const char* INTELLIGENT_PROJECTILE_TEXTURE_128x128 = INTELLIGENT_TOWER_TEXTURE_128x128;

		const char* GUI_SELECTION_TEXTURE_128x128 = "res/textures/selectedTowerGUI_128x128.png";
		const char* SPAWN_TEXTURE_128X128 = "res/textures/spawn_128x128.png";
	}

	namespace Models {
		// possible only thanks to the static call to the static WindowManager creation
		// ... Indeed glewInit() was called only at GameEngine creation
		// which happens later than below

		TexturedModel* tileSelectionModel = ModelLoader::getInstance("Loading tile selection model..")->loadFlatRectangleModel(ModelBank::Textures::SELECT_TEXTURE_128x128);

		TexturedModel* sampleSelectionModel = ModelLoader::getInstance("Loading sample selection model..")->loadFlatRectangleModel(ModelBank::Textures::SAMPLE_TOWER_TEXTURE_128x128);

		TexturedModel* intelligentSelectionModel = ModelLoader::getInstance("Loading intelligent selection model ..")->loadFlatRectangleModel(ModelBank::Textures::INTELLIGENT_TOWER_TEXTURE_128x128);

		TexturedModel* sampleAsteroidModel = ModelLoader::getInstance("Loading sample asteroid model..")->loadCubeModel(ModelBank::Textures::SAMPLE_ASTEROID_TEXTURE_128x128, Configs::SAMPLE_ASTEROID_SIZE);

		TexturedModel* sampleTowerModel = ModelLoader::getInstance("Loading sample tower model..")->loadCubeModel(ModelBank::Textures::SAMPLE_TOWER_TEXTURE_128x128, Configs::SAMPLE_TOWER_SIZE);

		TexturedModel* sampleProjectileModel = ModelLoader::getInstance("Loading sample projectile model..")->loadCubeModel(ModelBank::Textures::SAMPLE_PROJECTILE_TEXTURE_128x128, Configs::SAMPLE_PROJECTILE_SIZE);

		TexturedModel* intelligentTowerModel = ModelLoader::getInstance("Loading intelligent tower model..")->loadCubeModel(ModelBank::Textures::INTELLIGENT_TOWER_TEXTURE_128x128, Configs::INTELLIGENT_TOWER_SIZE);

		TexturedModel* intelligentProjectileModel = ModelLoader::getInstance("Loading intelligent projectile model..")->loadCubeModel(ModelBank::Textures::INTELLIGENT_PROJECTILE_TEXTURE_128x128, Configs::INTELLIGENT_PROJECTILE_SIZE);

		TexturedModel* spawnModel = ModelLoader::getInstance("Loading spawn model..")->loadCubeModel(ModelBank::Textures::SPAWN_TEXTURE_128X128, Configs::SPAWN_SIZE);

	}

	namespace Vertices {
		const unsigned int REC_VERTICES_SIZE = 12 * sizeof(float);
		const unsigned int CUBE_VERTICES_SIZE = 12 * 6 * sizeof(float);

		float RECTANGLE_VERTICES[] = {
			-0.5f, 0.5f, 0.0f,// top left 
			0.5f, 0.5f, 0.0f,// top right
			0.5f, -0.5f, 0.0f,// bottom right
			-0.5f, -0.5f, 0.0f,// bottom left
		};

		float RECTANGLE_VERTICES_2D[] = {
			-1.0f, 1.0f,
			-1.0f, -1.0f,
			1.0f, 1.0f,
			1.0f, -1.0f
		};

		float* generateRectangleVertices(float w, float h) {
			float* rectVertices = new float[12]{
				-w, h, 0.0f,
				-w, -h, 0.0f,
				w, h, 0.0f,
				w, -h, 0.0f,
			};

			return rectVertices;
		}

		// cube vertices, tex ... info
		// took on the net ofc
		float* generateCubeVertices(float size) {
			float* cubeVertices = new float[12 * 6]{
				size, -size, -size,
				size, -size, size,
				-size, -size, size,
				-size, -size, -size,

				size, size, -size,
				-size, size, -size,
				-size, size, size,
				size, size, size,

				size, -size, -size,
				size, size, -size,
				size, size, size,
				size, -size, size,

				size, -size, size,
				size, size, size,
				-size, size, size,
				-size, -size, size,

				-size, -size, size,
				-size, size, size,
				-size, size, -size,
				-size, -size, -size,

				size, size, -size,
				size, -size, -size,
				-size, -size, -size,
				-size, size, -size

			};
			return cubeVertices;
		}
	}

	namespace Indices {
		const unsigned int REC_INDICES_SIZE = 6 * sizeof(int);
		const unsigned int CUBE_INDICES_SIZE = 12 * 3 * sizeof(int);

		int RECTANGLE_INDICES[] = {
			0, 1, 2, // top left triangle
			2, 3, 0, // bot right triangle
		};

		int CUBE_INDICES[] = {
			0, 1, 3,
			3, 1, 2,
			4, 5, 7,
			7, 5, 6,
			8, 9, 11,
			11, 9, 10,
			12, 13, 15,
			15, 13, 14,
			16, 17, 19,
			19, 17, 18,
			20, 21, 23,
			23, 21, 22,
		};
	}

	namespace TextureCoords {
		const unsigned int REC_TEX_COORDS_SIZE = 8 * sizeof(float);
		const unsigned int CUBE_TEX_COORDS_SIZE = 4 * 2 * 6 * sizeof(float);

		float RECTANGLE_TEX_COORDS[] = {
			0.0f, 0.0f, // top left
			0.0f, 1.0f, // bot left
			1.0f, 1.0f, // bot right
			1.0f, 0.0f, // top right
		};

		float CUBE_TEX_COORDS[] = {
			0, 0,
			0, 1,
			1, 1,
			1, 0,

			0, 0,
			0, 1,
			1, 1,
			1, 0,

			0, 0,
			0, 1,
			1, 1,
			1, 0,

			0, 0,
			0, 1,
			1, 1,
			1, 0,

			0, 0,
			0, 1,
			1, 1,
			1, 0,

			0, 0,
			0, 1,
			1, 1,
			1, 0,
		};
	}

	namespace Normals {
		const unsigned int RECTANGLE_NORMALS_SIZE = 3 * 4 * sizeof(float);
		const unsigned int CUBE_NORMALS_SIZE = 3 * 4 * 6 * sizeof(float);

		float RECTANGLE_NORMALS[]{
			-0.5f, 0.5f, 0.0f, // top left 
			0.5f, 0.5f, 0.0f,// top right
			0.5f, -0.5f, 0.0f,// bottom right
			-0.5f, -0.5f, 0.0f,// bottom left
		};

		float CUBE_NORMALS[] = {
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,

			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,

			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,

			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,

			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f
		};
	}
}