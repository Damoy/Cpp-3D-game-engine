#include "TexturedModel.h"


const float TexturedModel::UNKNOWN_SIZE = -1.0f;

TexturedModel::TexturedModel(RawModel* rm, ModelTexture* mt, float fsize)
	: model(rm), texture(mt), size(fsize){

}

TexturedModel::TexturedModel(RawModel* rm, ModelTexture* mt)
	: model(rm), texture(mt), size(UNKNOWN_SIZE) {

}

TexturedModel::~TexturedModel(){
	// One could be used by multiple
	// delete model;
	// delete texture;
}

RawModel* TexturedModel::getRawModel() const { return model; }
ModelTexture* TexturedModel::getTexture() const { return texture; }
unsigned int TexturedModel::getTextureID() const { return texture->getID(); }
float TexturedModel::getSize() const { return size; }
bool TexturedModel::isSizeSet() const { return size != UNKNOWN_SIZE; } // float compare