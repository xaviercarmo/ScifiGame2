#include "Globals.h"
#include "CollisionDetection.h"
#include <cstdlib>

Polyhedron::Polyhedron(glm::vec3 dimensions, glm::vec3 position, float mass, bool stationary) : dimensions(dimensions), position(position), mass(mass), stationary(stationary)
{
	setStaticFrictionConstant(0.8);
	setKineticFrictionConstant(0.6);
}

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

void Polyhedron::applyPhysics() //possibly this kind of physics is better for objects, projectiles etc. but not for humanoids (as we dont move "smoothly" and this might be overkill
{
	//if (surfaceChanged())
	//setStaticFrictionConstant(newVal); //later, can evaluate the surface object is on and change friction constants so these setters actually do something (also don't need to evaluate them unless the terrain has changed, since we have one terrain ive ommitted them)

	force.y += mass * globals::gravityAccel;
	glm::vec3 vecDirections = getVecDirections(velocity);
	float absForceX = abs(force.x);
	float absForceZ = abs(force.z);
	bool baseTouching = baseInContact();

	if (baseTouching) {
		applyContactFriction(velocity.x, vecDirections.x, force.x);
		applyContactFriction(velocity.z, vecDirections.z, force.z);
	}

	velocity += (force / mass) * globals::dtSeconds;

	glm::vec3 newVecDirections = getVecDirections(velocity);

	if (baseTouching)
	{
		handleFrictionFlip(velocity.x, vecDirections.x, newVecDirections.x, force.x);
		handleFrictionFlip(velocity.z, vecDirections.z, newVecDirections.z, force.z);
	}

	for (auto polyhedron : globals::polyhedrons)
	{
		collisionDetection::correctPolyhedrons(this, &polyhedron);
	}

	position += velocity * glm::vec3{ -1, 1, 1 };

	//velocity.x *= 0.95;
	//velocity.z *= 0.95;

	//printf("vel x %f, vel z %f\n", velocity.x, velocity.z);

	force *= 0; //reset forces, anything that wants to continue to apply a force can do so at its own leisure lol
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

glm::vec3 Polyhedron::getVecDirections(glm::vec3 vec)
{
	glm::vec3 result{ 0, 0, 0 };

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
		if (position.y == polyhedron.position.y + polyhedron.dimensions.y && collisionDetection::detectRectangleCollision(position.x, position.z, dimensions.x, dimensions.z, polyhedron.position.x, polyhedron.position.z, polyhedron.dimensions.x, polyhedron.dimensions.z))
		{
			return true;
		}
	}

	return false;
}