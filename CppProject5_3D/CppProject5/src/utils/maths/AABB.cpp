#include "AABB.h"


AABB::AABB(float x1, float y1, float z1, float x2, float y2, float z2){
	minX = Maths::min(x1, x2);
	minY = Maths::min(y1, y2);
	minZ = Maths::min(z1, z2);

	maxX = Maths::max(x1, x2);
	maxY = Maths::max(y1, y2);
	maxZ = Maths::max(z1, z2);
}

AABB::~AABB(){
}

bool AABB::collide(AABB& with) const{
	return collide(with.minX, with.minY, with.minZ, with.maxX, with.maxY, with.maxZ);
}

bool AABB::collide(float x1, float y1, float z1, float x2, float y2, float z2) const {
	return minX < x2 && maxX > x1
		&& minY < y2 && maxY > y1
		&& minZ < z2 && maxZ > z1;
}

void AABB::update(float x1, float y1, float z1, float x2, float y2, float z2) {
	minX = Maths::min(x1, x2);
	minY = Maths::min(y1, y2);
	minZ = Maths::min(z1, z2);

	maxX = Maths::max(x1, x2);
	maxY = Maths::max(y1, y2);
	maxZ = Maths::max(z1, z2);
}

// getters
float AABB::getMinX() const { return minX; }
float AABB::getMinY() const { return minY; }
float AABB::getMinZ() const { return minZ; }
float AABB::getMaxX() const { return maxX; }
float AABB::getMaxY() const { return maxY; }
float AABB::getMaxZ() const { return maxZ; }

