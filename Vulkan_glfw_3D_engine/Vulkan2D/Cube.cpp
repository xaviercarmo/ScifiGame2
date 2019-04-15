#include "Cube.h"
#include "Globals.h"
#include "CollisionDetection.h"

Cube::Cube(float size, glm::vec3 position, float mass, bool stationary) : Polyhedron(glm::vec3{ size, size, size }, position, mass, stationary)
{
	vkObjectIndex = globals::gfx.addObject(position, glm::vec3(1,1,1) * size, 1);
}

void Cube::perLoop()
{
	applyPhysics();
}

void Cube::applyPhysics()
{
	if (!stationary)
	{
		force.y += mass * globals::gravityAccel;

		glm::ivec3 vecDirections = getVecDirections(velocity);

		bool baseTouching = baseInContact();

		if (baseTouching)
		{
			applyContactFriction(velocity.x, vecDirections.x, force.x);
			applyContactFriction(velocity.z, vecDirections.z, force.z);
		}

		velocity += (force / mass) * globals::dtSeconds;

		glm::ivec3 newVecDirections = getVecDirections(velocity);

		if (baseTouching)
		{
			handleFrictionFlip(velocity.x, vecDirections.x, newVecDirections.x, force.x);
			handleFrictionFlip(velocity.z, vecDirections.z, newVecDirections.z, force.z);
		}

		adjustPosition();

		force *= 0;
	}
}

void Cube::adjustPosition()
{
	for (auto polyhedron : globals::polyhedrons)
	{
		collisionDetection::correctPolyhedrons(*this, *polyhedron);
	}

	position += velocity * glm::vec3{ -1, 1, 1 };

	setVkObjectPosition(position);
}
