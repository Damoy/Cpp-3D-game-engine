#pragma once

#include "utils\maths\Maths.h"

/*
	A classic axis-aligned-bounding-box class.
*/
class AABB{
private:
	// positions
	float minX;
	float minY;
	float minZ;
	float maxX;
	float maxY;
	float maxZ;

public:
	AABB(float x1, float y1, float z1, float x2, float y2, float z2);
	~AABB();

	// getters
	float getMinX() const;
	float getMinY() const;
	float getMinZ() const;
	float getMaxX() const;
	float getMaxY() const;
	float getMaxZ() const;

	// Updates the box
	void update(float x1, float y1, float z1, float x2, float y2, float z2);
	// Does the box collide with another
	bool collide(AABB& box) const;
	// Does the box collide with this given positions
	bool collide(float x1, float y1, float z1, float x2, float y2, float z2) const;
};

