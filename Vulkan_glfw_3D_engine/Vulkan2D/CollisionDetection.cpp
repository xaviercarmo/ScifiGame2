#include "CollisionDetection.h"

namespace collisionDetection {
	struct Rectangle
	{
		float x;
		float y;
		float width;
		float height;
		float xVel;
		float yVel;
	};

	bool detectRectangleCollision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
		if (x1 + w1 > x2 && x1 < x2 + w2 && y1 + h1 > y2 && y1 < y2 + h2) {
			return true;
		}
		return false;
	}

	//assumes object two is stationary at the moment
	bool detectRectangleCollision2(Rectangle r1, Rectangle r2) {
		if (r1.x + r1.width + r1.xVel > r2.x && r1.x + r1.xVel < r2.x + r2.width && r1.y + r1.height + r1.yVel > r2.y && r1.y + r1.yVel < r2.y + r2.height) {
			return true;
		}

		return false;
	}

	void correctCollisionBoxes(CollisionBox* b1, CollisionBox* b2) {
		//collision within xy
		if (detectRectangleCollision(b1->position.x, b1->position.y, b1->dimensions.x, b1->dimensions.y, b2->position.x, b2->position.y, b2->dimensions.x, b2->dimensions.y)) {
			//from z negative side
			if (b1->position.z >= b2->position.z + b2->dimensions.z && b1->position.z + b1->velocity.z < b2->position.z + b2->dimensions.z) {
				b1->velocity.z = 0;
				b1->position.z = b2->position.z + b2->dimensions.z;
			}
			//from z negative side
			if (b1->position.z + b1->dimensions.z <= b2->position.z && b1->position.z + b1->dimensions.z + b1->velocity.z > b2->position.z) {
				b1->velocity.z = 0;
				b1->position.z = b2->position.z - b1->dimensions.z;
			}
		}
		//collision within xz
		if (detectRectangleCollision(b1->position.x, b1->position.z, b1->dimensions.x, b1->dimensions.z, b2->position.x, b2->position.z, b2->dimensions.x, b2->dimensions.z)) {
			//from y negative side
			if (b1->position.y >= b2->position.y + b2->dimensions.y && b1->position.y + b1->velocity.y < b2->position.y + b2->dimensions.y) {
				b1->velocity.y = 0;
				b1->position.y = b2->position.y + b2->dimensions.y;
			}
			//from y negative side
			if (b1->position.y + b1->dimensions.y - 0.01f <= b2->position.y && b1->position.y + b1->dimensions.y + b1->velocity.y > b2->position.y) {
				b1->velocity.y = 0;
				b1->position.y = b2->position.y - b1->dimensions.y;
			}
		}
		//collision within zy
		if (detectRectangleCollision(b1->position.z, b1->position.y, b1->dimensions.z, b1->dimensions.y, b2->position.z, b2->position.y, b2->dimensions.z, b2->dimensions.y)) {
			//from x positive side
			if (b1->position.x >= b2->position.x + b2->dimensions.x && b1->position.x + b1->velocity.x < b2->position.x + b2->dimensions.x) {
				b1->velocity.x = 0;
				b1->position.x = b2->position.x + b2->dimensions.x;
			}
			//from x negative side
			if (b1->position.x + b1->dimensions.x <= b2->position.x && b1->position.x + b1->dimensions.x + b1->velocity.x > b2->position.x) {
				b1->velocity.x = 0;
				b1->position.x = b2->position.x - b1->dimensions.x;
			}
		}
	}

	//need to make this check if either polyhedron is stationary (should be p2 if so). if it is do not ever adjust its position.
	void correctPolyhedrons(Polyhedron* p1, Polyhedron* p2)
	{
		Rectangle p1RectXY = Rectangle{ p1->position.x, p1->position.y, p1->dimensions.x, p1->dimensions.y, -p1->velocity.x, p1->velocity.y };
		Rectangle p1RectXZ = Rectangle{ p1->position.x, p1->position.z, p1->dimensions.x, p1->dimensions.z, -p1->velocity.x, p1->velocity.z };
		Rectangle p1RectZY = Rectangle{ p1->position.z, p1->position.y, p1->dimensions.z, p1->dimensions.y, p1->velocity.z, p1->velocity.y };

		Rectangle p2RectXY = Rectangle{ p2->position.x, p2->position.y, p2->dimensions.x, p2->dimensions.y, -p2->velocity.x, p2->velocity.y };
		Rectangle p2RectXZ = Rectangle{ p2->position.x, p2->position.z, p2->dimensions.x, p2->dimensions.z, -p2->velocity.x, p2->velocity.z };
		Rectangle p2RectZY = Rectangle{ p2->position.z, p2->position.y, p2->dimensions.z, p2->dimensions.y, p2->velocity.z, p2->velocity.y };

		//collision within xy
		if (detectRectangleCollision2(p1RectXY, p2RectXY))
		{
			if (p1->position.z >= p2->position.z + p2->dimensions.z && p1->position.z + p1->velocity.z < p2->position.z + p2->dimensions.z)
			{
				p1->velocity.z = 0;
				p1->position.z = p2->position.z + p2->dimensions.z;
			}
			else if (p1->position.z + p1->dimensions.z <= p2->position.z && p1->position.z + p1->dimensions.z + p1->velocity.z > p2->position.z)
			{
				p1->velocity.z = 0;
				p1->position.z = p2->position.z - p1->dimensions.z;
			}
		}

		//collision within xz
		if (detectRectangleCollision2(p1RectXZ, p2RectXZ))
		{
			if (p1->position.y >= p2->position.y + p2->dimensions.y && p1->position.y + p1->velocity.y < p2->position.y + p2->dimensions.y)
			{
				p1->velocity.y = 0;
				p1->position.y = p2->position.y + p2->dimensions.y;
			}
			else if (p1->position.y + p1->dimensions.y - 0.01f <= p2->position.y && p1->position.y + p1->dimensions.y + p1->velocity.y > p2->position.y)
			{
				p1->velocity.y = 0;
				p1->position.y = p2->position.y - p1->dimensions.y;
			}
		}

		//collision within zy, looks weird because we flip x, and so our velocity is flipped also
		if (detectRectangleCollision2(p1RectZY, p2RectZY))
		{
			if (p1->position.x + p1->dimensions.x <= p2->position.x && p1->position.x + p1->dimensions.x + (-p1->velocity.x) > p2->position.x)
			{
				p1->velocity.x = 0;
				p1->position.x = p2->position.x - p1->dimensions.x;
			}
			else if (p1->position.x >= p2->position.x + p2->dimensions.x && p1->position.x + (-p1->velocity.x) < p2->position.x + p2->dimensions.x)
			{
				p1->velocity.x = 0;
				p1->position.x = p2->position.x + p2->dimensions.x;
			}
		}
	}
}

//Collision bugs
//	1. if going too fast can clip to object behind closest object
//  2. current clips through objects when edge-to-edge contact occurs