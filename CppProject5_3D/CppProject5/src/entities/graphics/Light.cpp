#include "Light.h"


Light::Light(float x, float y, float z, float r, float g, float b) {
	position = glm::vec3(x, y, z);
	color = new Color(r, g, b, 1.0f);
}

Light::~Light() {
	delete color;
}

// getters
glm::vec3 Light::getPosition() const { return position; }
float Light::getX() const { return position.x; }
float Light::getY() const { return position.y; }
float Light::getZ() const { return position.z; }
Color* Light::getColor() const { return color; }

// setters
void Light::setX(float x) { position.x = x; }
void Light::setY(float y) { position.y = y; }
void Light::setZ(float z) { position.z = z; }

