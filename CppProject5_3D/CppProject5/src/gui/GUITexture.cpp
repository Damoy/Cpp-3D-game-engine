#include "GUITexture.h"


GUITexture::GUITexture(unsigned int tID, unsigned int width, unsigned int height, glm::vec2 pos, glm::vec2 s)
	:	ModelTexture(tID, width, height),
		position(pos), scale(s){
}

GUITexture::~GUITexture(){
}

unsigned int GUITexture::getID() const {
	return ID;
}

glm::vec2 GUITexture::getPosition() const {
	return position;
}

glm::vec2 GUITexture::getScale() const {
	return scale;
}