#include "CollisionDetection.h"

namespace collisionDetection {
	//assumes object two is stationary at the moment
	bool detectRectangleCollision(Rectangle& r1, Rectangle& r2) {
		if (r1.x + r1.width + r1.xVel * r1.xVelMult > r2.x && r1.x + r1.xVel * r1.xVelMult < r2.x + r2.width && r1.y + r1.height + r1.yVel * r1.yVelMult > r2.y && r1.y + r1.yVel * r1.yVelMult < r2.y + r2.height) {
			return true;
		}

		return false;
	}

	//need to make this check if either polyhedron is stationary (should be p2 if so). if it is do not ever adjust its position.
	void correctPolyhedrons(Polyhedron& p1, Polyhedron& p2)
	{
		std::vector<bool> flags(6, false); //useful for debugging

		Rectangle p1RectXY = Rectangle{ p1.position.x, p1.position.y, p1.dimensions.x, p1.dimensions.y, p1.velocity.x, -1, p1.velocity.y, 1 };
		Rectangle p1RectXZ = Rectangle{ p1.position.x, p1.position.z, p1.dimensions.x, p1.dimensions.z, p1.velocity.x, -1, p1.velocity.z, 1 };
		Rectangle p1RectZY = Rectangle{ p1.position.z, p1.position.y, p1.dimensions.z, p1.dimensions.y, p1.velocity.z, 1, p1.velocity.y, 1 };

		Rectangle p2RectXY = Rectangle{ p2.position.x, p2.position.y, p2.dimensions.x, p2.dimensions.y, p2.velocity.x, -1, p2.velocity.y, 1 };
		Rectangle p2RectXZ = Rectangle{ p2.position.x, p2.position.z, p2.dimensions.x, p2.dimensions.z, p2.velocity.x, -1, p2.velocity.z, 1 };
		Rectangle p2RectZY = Rectangle{ p2.position.z, p2.position.y, p2.dimensions.z, p2.dimensions.y, p2.velocity.z, 1, p2.velocity.y, 1 };

		//collision within xy
		if (detectRectangleCollision(p1RectXY, p2RectXY))
		{
			if (p1.position.z >= p2.position.z + p2.dimensions.z && p1.position.z + p1.velocity.z < p2.position.z + p2.dimensions.z)
			{
				p1.velocity.z = 0;
				p1.position.z = p2.position.z + p2.dimensions.z;
				flags[0] = true; //xy coming back
			}
			else if (p1.position.z + p1.dimensions.z <= p2.position.z && p1.position.z + p1.dimensions.z + p1.velocity.z > p2.position.z)
			{
				p1.velocity.z = 0;
				p1.position.z = p2.position.z - p1.dimensions.z;
				flags[1] = true; //xy going forward
			}
		}

		//collision within xz
		if (detectRectangleCollision(p1RectXZ, p2RectXZ))
		{
			if (p1.position.y >= p2.position.y + p2.dimensions.y && p1.position.y + p1.velocity.y < p2.position.y + p2.dimensions.y)
			{
				p1.velocity.y = 0;
				p1.position.y = p2.position.y + p2.dimensions.y;
				flags[2] = true; //xz from above
			}
			else if (p1.position.y + p1.dimensions.y - 0.01f <= p2.position.y && p1.position.y + p1.dimensions.y + p1.velocity.y > p2.position.y)
			{
				p1.velocity.y = 0;
				p1.position.y = p2.position.y - p1.dimensions.y;
				flags[3] = true; //xz from below
			}
		}

		//collision within zy, looks weird because we flip x, and so our velocity is flipped also
		if (detectRectangleCollision(p1RectZY, p2RectZY))
		{
			if (p1.position.x + p1.dimensions.x <= p2.position.x && p1.position.x + p1.dimensions.x + (-p1.velocity.x) > p2.position.x)
			{
				p1.velocity.x = 0;
				p1.position.x = p2.position.x - p1.dimensions.x;
				flags[4] = true; //zy from right
			}
			else if (p1.position.x >= p2.position.x + p2.dimensions.x && p1.position.x + (-p1.velocity.x) < p2.position.x + p2.dimensions.x)
			{
				p1.velocity.x = 0;
				p1.position.x = p2.position.x + p2.dimensions.x;
				flags[5] = true; //zy from left
			}
		}
	}
}

//Collision bugs
//	1. if going too fast can clip to object behind closest object