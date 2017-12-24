/* -- For stbi_load use -- */
#define STB_IMAGE_IMPLEMENTATION
#include "STBI\stb_image.h"

#include "TextureLoader.h"
#include "utils\checkers\Checker.h"
#include "utils\logs\Logs.h"

unsigned int TextureLoader::texturesCount = 0;
std::map<const char*, TextureLoader::TextureBundle>* TextureLoader::textureMemory = new std::map<const char*, TextureLoader::TextureBundle>();


int TextureLoader::getTextureAtlas(unsigned short number) {
	return GL_TEXTURE0 + number;
}

/*
	--- [MEMORY USING] ---
	Generates a new texture ID,
	actives an openGL texture (TEXTURE0),
	binds it as a 2D texture,
	sets the texture wrapping and filtering options,
	loads, thanks to stbi library, the textureFile,
	specifies the 2D texture image,
	generates the mipmap for it (option here ?),
	releases the data consumed to generate the texture file.
*/
TextureLoader::TextureBundle TextureLoader::generateTexture(const char* textureFilePath, unsigned short textureAtlasHint) {
	std::map<const char*, TextureBundle>::iterator mapIT;
	mapIT = textureMemory->find(textureFilePath);

	// if already existing we return the bundle associated
	if (mapIT != textureMemory->end()) {
		Logs::println("Texture already generated.");
		return (*mapIT).second;
	}

	// generates a texture ID
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int textureAtlas = getTextureAtlas(textureAtlasHint);
	// actives one GL texture
	glActiveTexture(textureAtlas);
	// binds it to our generated texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// sets the texture wrapping and filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	int width;
	int height;
	int channels;

	// loads the texture file into a char array
	unsigned char* textureData = stbi_load(textureFilePath, &width, &height, &channels, 0);

	// checks if the loading succeeded
	Checker::Loaders::checkTextureLoadingState(textureData);

	// Specifies the 2D texture using RGBA or RGB
	// depending on the channels value (using A component or not).
	// Each component is clamped to the range [0,1].
	if (channels == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
	else if (channels == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);

	// mipmapping: better distance rendering performance
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// add distance before mipmapping
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.3f);

	// frees the texture data now that we used it on glTexImage2D
	stbi_image_free(textureData);

	texturesCount++;

	TextureBundle bundle;
	bundle.ID = textureID;
	bundle.width = width;
	bundle.height = height;

	// add it to the memory
	(*textureMemory)[textureFilePath] = bundle;

	return bundle;
}

ModelTexture* TextureLoader::generateModelTexture(const char* textureFilePath) {
	TextureBundle bundle = generateTexture(textureFilePath, Configs::MODEL_TEXTURE_ATLAS);
	unsigned int textureID = bundle.ID;
	unsigned int width = bundle.width;
	unsigned int height = bundle.height;
	return new ModelTexture(textureID, width, height);
}

GUITexture* TextureLoader::generateGUITexture(const char* textureFilePath, glm::vec2 position, glm::vec2 scale) {
	TextureBundle bundle = generateTexture(textureFilePath, Configs::GUI_TEXTURE_ATLAS);
	unsigned int textureID = bundle.ID;
	unsigned int width = bundle.width;
	unsigned int height = bundle.height;
	return new GUITexture(textureID, width, height, position, scale);
}

int TextureLoader::getBaseModelTextureAtlas() {
	return GL_TEXTURE0 + Configs::MODEL_TEXTURE_ATLAS;
}

int TextureLoader::getGUITextureAtlas() {
	return GL_TEXTURE0 + Configs::GUI_TEXTURE_ATLAS;
}

