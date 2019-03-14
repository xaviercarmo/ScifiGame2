#pragma once
#include "CollisionBox.h"
#include "Polyhedron.h"

namespace collisionDetection {
	void correctCollisionBoxes(CollisionBox* b1, CollisionBox* b2);
	void correctPolyhedrons(Polyhedron* p1, Polyhedron* p2);
}