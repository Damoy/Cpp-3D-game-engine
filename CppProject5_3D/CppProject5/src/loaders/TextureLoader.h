#pragma once

#include <iostream>
#include "GL\glew.h"
#include "GLM\glm.hpp"
#include "textures\ModelTexture.h"
#include "gui\GUITexture.h"
#include "gameEngine\Configs.h"

#include <map>

/* Static texture loading class. */
class TextureLoader{
private:
	TextureLoader();

	// Struct used for multiple function return data
	typedef struct TextureBundle {
		unsigned int ID;
		unsigned int width;
		unsigned int height;
	} TextureBundle;
	
	// a texture memory, path, bundle
	static std::map<const char*, TextureBundle>* textureMemory;
	// counts the textures
	static unsigned int texturesCount;

	// generates a texture (while activating it...)
	static TextureBundle generateTexture(const char* textureFilePath, unsigned short textureAtlasHint);

	// get the opengl texture atlas based on a index
	static int getTextureAtlas(unsigned short number);

public:
	/*
	Generates a new texture ID,
	actives an openGL texture (TEXTURE0),
	binds it as a 2D texture,
	sets the texture wrapping and filtering options,
	loads, thanks to stbi library, the textureFile,
	specifies the 2D texture image,
	generates the mipmap for it (option here ?),
	releases the data consumed to generate the texture file
	and returns a new ModelTexture of the generated textureID.
	*/
	static ModelTexture* generateModelTexture(const char* texturePath);

	// Generates a gui texture
	static GUITexture* generateGUITexture(const char* texturePath, glm::vec2 position, glm::vec2 scale);

	static int getBaseModelTextureAtlas();
	static int getGUITextureAtlas();
};

