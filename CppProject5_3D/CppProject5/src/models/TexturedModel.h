#pragma once

#include "textures\ModelTexture.h"
#include "RawModel.h"

/* 
	On this case, I prefer to use the model texture as
	a parameter of the TexturedModel class than inheriting from it
	even if am aware it sounds strange and may be bad.
*/
class TexturedModel{
private:
	const static float UNKNOWN_SIZE;
	// the raw model
	RawModel* model;
	// the texture
	ModelTexture* texture;
	float size;

public:
	TexturedModel(RawModel* model, ModelTexture* texture, float size);
	TexturedModel::TexturedModel(RawModel* rm, ModelTexture* mt);
	~TexturedModel();

	RawModel* getRawModel() const;
	ModelTexture* getTexture() const;
	unsigned int getTextureID() const;
	float getSize() const;
	bool isSizeSet() const;
};

