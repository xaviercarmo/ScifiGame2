#include "Globals.h"
#include "CollisionDetection.h"
#include <cstdlib>

Polyhedron::Polyhedron(glm::vec3 dimensions, glm::vec3 position, float mass, bool stationary) : dimensions(dimensions), position(position), mass(mass), stationary(stationary)
{
	vkObjectIndex = -1;

	setStaticFrictionConstant(0.8f);
	setKineticFrictionConstant(0.6f);
}

//void Polyhedron::perLoop()
//{
//}

void Polyhedron::setStaticFrictionConstant(float newVal)
{
	staticFrictionConstant = newVal >= kineticFrictionConstant ? newVal : staticFrictionConstant; //should throw invalid arg exception probably
	positiveStaticFrictionForce = staticFrictionConstant * (mass * -globals::gravityAccel); //this assumes you are on a horizontal plane, will need to be adjusted (has to take perp. component of normal force) when we start rotating things
}

void Polyhedron::setKineticFrictionConstant(float newVal)
{
	kineticFrictionConstant = newVal <= staticFrictionConstant && newVal >= 0 ? newVal : kineticFrictionConstant;
	positiveKineticFrictionForce = kineticFrictionConstant * (mass * -globals::gravityAccel);
}

void Polyhedron::applyContactFriction(float velocity, int direction, float& force)
{
	float absForce = abs(force);
	if (velocity == 0 && absForce < positiveStaticFrictionForce)
	{
		force = 0;
	}
	else if (velocity == 0 && absForce > positiveStaticFrictionForce)
	{
		force += positiveStaticFrictionForce * -direction;
	}
	else if (velocity != 0)
	{
		force += positiveKineticFrictionForce * -direction;
	}
}

void Polyhedron::handleFrictionFlip(float& velocity, int oldDirection, int newDirection, float force)
{
	if (newDirection != oldDirection && abs(force) == positiveKineticFrictionForce)
	{
		velocity = 0;
	}
}

glm::ivec3 Polyhedron::getVecDirections(glm::vec3 vec)
{
	glm::ivec3 result{ 0, 0, 0 };

	if (vec.x > 0)
	{
		result.x = 1;
	}
	else if (vec.x < 0)
	{
		result.x = -1;
	}

	if (vec.y > 0)
	{
		result.y = 1;
	}
	else if (vec.y < 0)
	{
		result.y = -1;
	}

	if (vec.z > 0)
	{
		result.z = 1;
	}
	else if (vec.z < 0)
	{
		result.z = -1;
	}

	return result;
}

bool Polyhedron::baseInContact()
{
	for (auto polyhedron : globals::polyhedrons)
	{
		collisionDetection::Rectangle playerBase = collisionDetection::Rectangle{ position.x, position.z, dimensions.x, dimensions.z, velocity.x, 0, velocity.y, 0};
		collisionDetection::Rectangle polyhedronTop = collisionDetection::Rectangle{ polyhedron->position.x, polyhedron->position.z, polyhedron->dimensions.x, polyhedron->dimensions.z, polyhedron->velocity.x, 0, polyhedron->velocity.z, 0 };
		
		if (position.y == polyhedron->position.y + polyhedron->dimensions.y && collisionDetection::detectRectangleCollision(playerBase, polyhedronTop))
		{
			return true;
		}
	}

	return false; //one day this should decide which face is the "base"
}

void Polyhedron::setVkObjectPosition(glm::vec3 position)
{
	globals::gfx.moveObject(vkObjectIndex, position);
}