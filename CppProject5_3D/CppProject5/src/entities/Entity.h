#pragma once

#include "GLM\glm.hpp"
#include "models\TexturedModel.h"
#include "utils\maths\AABB.h"

/*
	The Entity is the main object of the project.
	Most of visible in-game content will inherit from it.
	Even if it does not have virtual pure method, it should not instanciated.
*/
class Entity{
protected:
	// the entity's textured model
	TexturedModel* model;
	// the entity position
	glm::vec3 position;
	// the entity rotation
	glm::vec3 rotation;
	// the entity axis-aligned bounding box
	AABB* box;

	// the entity scales
	float xScale;
	float yScale;
	float zScale;

	// the entity open
	float width;
	float height;

public:
	Entity(TexturedModel* model, float x, float y, float z, float rotX, float rotY, float rotZ, float xScale, float yScale, float zScale);
	Entity(TexturedModel* model, float x, float y, float z, float xScale, float yScale, float zScale);

	virtual ~Entity();

	// to increase position
	void incPos(float dx, float dy, float dz);
	void incPos(glm::vec3 with);

	void incX(float);
	void incY(float);
	void incZ(float);

	// to set position
	void setX(float);
	void setY(float);
	void setZ(float);
	void setPos(float x, float y, float z);
	void setPos(glm::vec3 pos);

	// to increase rotation
	void incRot(float dx, float dy, float dz);
	void incRot(glm::vec3 with);

	// to set rotation
	void setRotX(float rotX);
	void setRotY(float rotY);
	void setRotZ(float rotZ);

	void setRot(float x, float y, float z);
	void setRot(glm::vec3 rot);

	// getters
	TexturedModel* getModel() const;
	glm::vec3 getPosition() const;
	glm::vec3 getRotation() const;

	float getXScale() const;
	float getYScale() const;
	float getZScale() const;

	float getX() const;
	float getY() const;
	float getZ() const;
	float getRotX() const;
	float getRotY() const;
	float getRotZ() const;
	AABB* getAABB() const;


	// updates the entity
	virtual void update();
	// does the entity collide with another
	bool collide(Entity* with) const;
	// does the entity collide with the given data
	bool collide(float x1, float y1, float z1, float x2, float y2, float z2) const;

};

