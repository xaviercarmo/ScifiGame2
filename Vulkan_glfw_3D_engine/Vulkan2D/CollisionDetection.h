#pragma once
#include "CollisionBox.h"
#include "Polyhedron.h"

namespace collisionDetection {
	bool detectRectangleCollision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
	void correctCollisionBoxes(CollisionBox* b1, CollisionBox* b2);
	void correctPolyhedrons(Polyhedron* p1, Polyhedron* p2);
}