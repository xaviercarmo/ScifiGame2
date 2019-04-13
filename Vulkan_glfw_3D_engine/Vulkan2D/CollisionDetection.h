#pragma once
#include "CollisionBox.h"
#include "Polyhedron.h"

namespace collisionDetection
{
	struct Rectangle
	{
		float& x;
		float& y;
		float& width;
		float& height;
		float& xVel;
		int xVelMult;
		float& yVel;
		int yVelMult;
	};

	bool detectRectangleCollision(Rectangle& r1, Rectangle& r2);
	void correctPolyhedrons(Polyhedron& p1, Polyhedron& p2);
}