#include "ModelTexture.h"


ModelTexture::ModelTexture(unsigned int tex, unsigned int w, unsigned int h)
	: textureID(tex), width(w), height(h){

}

ModelTexture::ModelTexture(unsigned int ID)
	: textureID(ID), width(0), height(0) {

}

ModelTexture::~ModelTexture(){
}

unsigned int ModelTexture::getID() const { return textureID; }
unsigned int ModelTexture::getWidth() const { return width; }
unsigned int ModelTexture::getHeight() const { return height; }
