#pragma once
#include <vector>
#include "models\TexturedModel.h"

/*
	The ModelBank, used throughout the code to ease model data, texture, manipulation.
*/
namespace ModelBank{

	// simple tool
	template<typename T>
	std::vector<T>& generateVector(unsigned int capacity) {
		return *(new std::vector<T>(capacity));
	}

	namespace Textures {
		// textures paths
		extern const char* GREEN_TEXTURE_128x128;
		extern const char* GLASS_TEXTURE_64x64;
		extern const char* GRASS_TEXTURE_64x64;
		extern const char* GROUND_TEXTURE_64x64;
		extern const char* SPACE_TEXTURE_512x512;
		extern const char* GROUND_TEXTURE_128x128;
		extern const char* SELECT_TEXTURE_128x128;

		// sample related
		extern const char* SAMPLE_ASTEROID_TEXTURE_128x128;
		extern const char* SAMPLE_TOWER_TEXTURE_128x128;
		extern const char* SAMPLE_PROJECTILE_TEXTURE_128x128;
		extern const char* SAMPLE_MAP_TEXTURE_128x128;

		// intelligent tower related
		extern const char* INTELLIGENT_TOWER_TEXTURE_128x128;
		extern const char* INTELLIGENT_PROJECTILE_TEXTURE_128x128;

		// gui related
		extern const char* GUI_SELECTION_TEXTURE_128x128;

		// spawn related
		extern const char* SPAWN_TEXTURE_128X128;
	}

	namespace Models {
		// model storage
		extern TexturedModel* tileSelectionModel;
		extern TexturedModel* sampleSelectionModel;
		extern TexturedModel* intelligentSelectionModel;

		extern TexturedModel* sampleAsteroidModel;
		extern TexturedModel* sampleTowerModel;
		extern TexturedModel* sampleProjectileModel;
		extern TexturedModel* intelligentTowerModel;
		extern TexturedModel* intelligentProjectileModel;

		extern TexturedModel* spawnModel;
	}

	namespace Vertices {
		// vertices storage
		extern const unsigned int REC_VERTICES_SIZE;
		extern const unsigned int CUBE_VERTICES_SIZE;

		extern float RECTANGLE_VERTICES[];
		extern float RECTANGLE_VERTICES_2D[];

		extern float* generateRectangleVertices(float w, float h);
		extern float* generateCubeVertices(float size);
	}

	namespace Indices {
		// indices storage
		extern const unsigned int REC_INDICES_SIZE;
		extern const unsigned int CUBE_INDICES_SIZE;

		// rectangle indices
		extern int RECTANGLE_INDICES[];

		// cube indices
		extern int CUBE_INDICES[];
	}

	namespace TextureCoords {
		// texture coordinates storage
		extern const unsigned int REC_TEX_COORDS_SIZE;
		extern const unsigned int CUBE_TEX_COORDS_SIZE;

		// texture coordinates
		// has to be in same order than the vertices
		// model texture coordinates
		extern float RECTANGLE_TEX_COORDS[];

		// cube texture coordinates
		extern float CUBE_TEX_COORDS[];
	}

	namespace Normals {
		// normals storage
		extern const unsigned int CUBE_NORMALS_SIZE;
		extern const unsigned int RECTANGLE_NORMALS_SIZE;
		extern float CUBE_NORMALS[];
		extern float RECTANGLE_NORMALS[];
	}


}

