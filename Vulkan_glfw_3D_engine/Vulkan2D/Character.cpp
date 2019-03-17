#include "Character.h"
#include "CollisionDetection.h"

Character::Character(glm::vec3 dimensions, glm::vec3 position, float mass) : Polyhedron(dimensions, position, mass, false)
{
}

void Character::receiveInput()
{
	if (globals::input.keys.w)
	{
		force.z += moveForce;
	}

	if (globals::input.keys.a)
	{
		force.x += -moveForce;
	}

	if (globals::input.keys.s)
	{
		force.z += -moveForce;
	}

	if (globals::input.keys.d)
	{
		force.x += moveForce;
	}

	if (globals::input.keys.space)
	{
		//if (!jumped)
		if (touchingFloor())
		{
			jump();
		}
	}
	else
	{
		jumped = false;
	}

	if (globals::input.keys.leftShift)
	{
		
	}

	if (globals::input.keys.alt)
	{
		globals::gfx.setFreeLook(true);
	}
	else
	{
		globals::gfx.setFreeLook(false);
		globals::gfx.setCameraAngle(glm::vec3(0, -0.25, 1));
	}
}

void Character::jump()
{
	jumped = true;
	force.y += jumpForce;
}

bool Character::touchingFloor()
{
	for (auto polyhedron : globals::polyhedrons)
	{
		if (collisionDetection::detectRectangleCollision(position.x, position.z, dimensions.x, dimensions.z, polyhedron.position.x, polyhedron.position.z, polyhedron.dimensions.x, polyhedron.dimensions.z))
		{
			if (position.y == polyhedron.position.y + polyhedron.dimensions.y)
			{
				return true;
			}
		}
	}

	return false;
}