#include "Globals.h"
#include "CollisionDetection.h"
#include <cstdlib>

Polyhedron::Polyhedron(glm::vec3 dimensions, glm::vec3 position, float mass, bool stationary) : dimensions(dimensions), position(position), mass(mass), stationary(stationary)
{
	setPositiveStaticFrictionForce();
	setPositiveKineticFrictionForce();
}

void Polyhedron::applyPhysics() //possibly this kind of physics is better for objects, projectiles etc. but not for humanoids (as we dont move "smoothly" and this might be overkill
{
	//if (surfaceChanged())
	//setPositiveStaticFrictionForce(); //later, can evaluate the surface object is on and change friction constants so these setters actually do something (also don't need to evaluate them unless the terrain has changed, since we have one terrain ive ommitted them)
	//setPositiveKineticFrictionForce();

	//force.y += mass * globals::gravityAccel;
	glm::vec3 vecDirections = getVecDirections(velocity);
	float absForceX = abs(force.x);
	float absForceZ = abs(force.z);

	applyContactFriction(velocity.x, vecDirections.x, force.x);
	applyContactFriction(velocity.z, vecDirections.z, force.z);

	velocity += (force / mass) * globals::dtSeconds;

	glm::vec3 newVecDirections = getVecDirections(velocity);

	handleFrictionFlip(velocity.x, vecDirections.x, newVecDirections.x, force.x);
	handleFrictionFlip(velocity.z, vecDirections.z, newVecDirections.z, force.z);

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


void Polyhedron::setPositiveStaticFrictionForce() {
	positiveStaticFrictionForce = staticFrictionConstant * (mass * -globals::gravityAccel);
}

void Polyhedron::setPositiveKineticFrictionForce() {
	//this assumes you are on a horizontal plane, will need to be adjusted (has to take perp. component of normal force) when we start rotating things
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