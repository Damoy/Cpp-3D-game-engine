#include <iostream>

#include "GLM\glm.hpp"

#include "Entity.h"
#include "utils\logs\Logs.h"

Entity::Entity(TexturedModel* tm, float x, float y, float z, float rotX, float rotY, float rotZ, float xs, float ys, float zs)
	: model(tm), xScale(xs), yScale(ys), zScale(zs) {

	position = glm::vec3(x, y, z);
	rotation = glm::vec3(rotX, rotY, rotZ);

	// can totally be wrong , y ..
	width = xScale * model->getSize();
	height = yScale * model->getSize();

	// quick aabb, supposing entity x width == entity z width
	box = new AABB(x, y, z, x + width, y + height, z + width);
}

Entity::Entity(TexturedModel* model, float x, float y, float z, float xScale, float yScale, float zScale)
	: Entity(model, x, y, z, 0.0f, 0.0f, 0.0f, xScale, yScale, zScale){
}

Entity::~Entity() {
	delete box;
}

void Entity::update() {
	// update the AABB
	box->update(position.x, position.y, position.z, position.x + width, position.y + height, position.z + width);
}

void Entity::incPos(float dx, float dy, float dz) {
	position.x += dx;
	position.y += dy;
	position.z += dz;
}

void Entity::incPos(glm::vec3 v) {
	incPos(v.x, v.y, v.z);
}

void Entity::incRot(float dx, float dy, float dz) {
	rotation.x += dx;
	rotation.y += dy;
	rotation.z += dz;
}

void Entity::incRot(glm::vec3 v) {
	incRot(v.x, v.y, v.z);
}

void Entity::setPos(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;
}

void Entity::setPos(glm::vec3 pos) {
	setPos(pos.x, pos.y, pos.z);
}

void Entity::setRot(float x, float y, float z) {
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
}

void Entity::setRot(glm::vec3 rot) {
	setRot(rot.x, rot.y, rot.z);
}

void Entity::incX(float dx) {
	position.x += dx;
}

void Entity::setX(float newX) {
	position.x = newX;
}

void Entity::incY(float dy) {
	position.y += dy;
}

void Entity::setY(float newY) {
	position.y = newY;
}

void Entity::incZ(float dz) {
	position.z += dz;
}

void Entity::setZ(float newZ) {
	position.z = newZ;
}

void Entity::setRotX(float rotX) {
	rotation.x = rotX;
}

void Entity::setRotY(float rotY) {
	rotation.y = rotY;
}

void Entity::setRotZ(float rotZ) {
	rotation.z = rotZ;
}

bool Entity::collide(Entity* with) const {
	return box->collide(*with->getAABB());
}

bool Entity::collide(float x1, float y1, float z1, float x2, float y2, float z2) const {
	return box->collide(x1, y1, z1, x2, y2, z2);
}


// Getters
TexturedModel* Entity::getModel() const { return model; }
glm::vec3 Entity::getPosition() const { return position; }
glm::vec3 Entity::getRotation() const { return rotation; }
float Entity::getXScale() const { return xScale; }
float Entity::getYScale() const { return yScale; }
float Entity::getZScale() const { return zScale; }
float Entity::getX() const { return position.x; }
float Entity::getY() const { return position.y; }
float Entity::getZ() const { return position.z; }
float Entity::getRotX() const { return rotation.x; }
float Entity::getRotY() const { return rotation.y; }
float Entity::getRotZ() const { return rotation.z; }
AABB* Entity::getAABB() const { return box; }


