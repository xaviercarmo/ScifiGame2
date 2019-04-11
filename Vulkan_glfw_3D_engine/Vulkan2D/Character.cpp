#include "Character.h"
#include "CollisionDetection.h"

Character::Character(glm::vec3 dimensions, glm::vec3 position, float mass) : Polyhedron(dimensions, position, mass, false)
{
	vkObjectIndex = globals::gfx.addObject(position, glm::vec3(1,1,2), 0);

	setStaticFrictionConstant(0.9f);
	setKineticFrictionConstant(0.8f);
}

void Character::receiveInput()
{
	bool baseTouching = baseInContact();

	float forceToAdd = baseTouching ? moveForceGround : moveForceAir;
	float diagForceToAdd = baseTouching ? diagMoveForceGround : diagMoveForceAir;

	if (globals::input.keys.w)
	{
		moveForceVec.z += (globals::input.keys.a != globals::input.keys.d) ? diagForceToAdd : forceToAdd;
	}

	if (globals::input.keys.a)
	{
		moveForceVec.x -= (globals::input.keys.w != globals::input.keys.s) ? diagForceToAdd : forceToAdd;
	}

	if (globals::input.keys.s)
	{
		moveForceVec.z -= (globals::input.keys.a != globals::input.keys.d) ? diagForceToAdd : forceToAdd;
	}

	if (globals::input.keys.d)
	{
		moveForceVec.x += (globals::input.keys.w != globals::input.keys.s) ? diagForceToAdd : forceToAdd;
	}

	if (globals::input.keys.space && baseTouching)
	{
		jump();
	}

	if (globals::input.keys.leftShift)
	{
		force *= 0;
		moveForceVec *= 0;
		velocity *= 0;
		moveVel *= 0;
		position = glm::vec3{ 0.5, 2, 0.5 };
		setVkObjectPosition(position);
	}

	if (globals::input.keys.leftAlt)
	{
		globals::gfx.setFreeLook(true);
	}
	else
	{
		globals::gfx.setFreeLook(false);
		globals::gfx.setCameraAngle(glm::vec3(0, -0.25, 1));
	}
}

void Character::perLoop()
{
	receiveInput();
	applyPhysics();
}

void Character::jump()
{
	force.y += jumpForce;
}

void Character::applyPhysics()
{
	//if (surfaceChanged())
	//setStaticFrictionConstant(newVal); //later, can evaluate the surface object is on and change friction constants so these setters actually do something (also don't need to evaluate them unless the terrain has changed, since we have one terrain ive ommitted them)

	force.y += mass * globals::gravityAccel;

	glm::ivec3 vecDirections = getVecDirections(velocity);
	glm::ivec3 moveVecDirections = getVecDirections(moveVel);

	bool baseTouching = baseInContact();

	if (baseTouching)
	{
		applyContactFriction(velocity.x, vecDirections.x, force.x);
		applyContactFriction(velocity.z, vecDirections.z, force.z);

		applyContactFriction(moveVel.x, moveVecDirections.x, moveForceVec.x);
		applyContactFriction(moveVel.z, moveVecDirections.z, moveForceVec.z);
	}

	velocity += (force / mass) * globals::dtSeconds; //adds the acceleration in increments because instantaneous acceleration is per second (and this "apply physics" method gets called "dtSeconds" times per second)
	//^ this section adds forces from external effects (e.g. explosions, or being pushed)
	moveVel += (moveForceVec / mass) * globals::dtSeconds;
	//^ this is just the result of moving the player with wasd (which applies a force)
	limitMoveVel();

	glm::ivec3 newVecDirections = getVecDirections(velocity);
	glm::ivec3 newMoveVecDirections = getVecDirections(moveVel);

	if (baseTouching)
	{
		handleFrictionFlip(velocity.x, vecDirections.x, newVecDirections.x, force.x);
		handleFrictionFlip(velocity.z, vecDirections.z, newVecDirections.z, force.z);

		handleFrictionFlip(moveVel.x, moveVecDirections.x, newMoveVecDirections.x, moveForceVec.x);
		handleFrictionFlip(moveVel.z, moveVecDirections.z, newMoveVecDirections.z, moveForceVec.z);
	}

	adjustPosition();

	force *= 0;
	moveForceVec *= 0;
}

void Character::limitMoveVel()
{
	float speedToCompare = maxMoveSpeedGround;

	if (moveVel.x > speedToCompare)
	{
		moveVel.x = speedToCompare;
	}
	else if (moveVel.x < -speedToCompare)
	{
		moveVel.x = -speedToCompare;
	}

	if (moveVel.z > speedToCompare)
	{
		moveVel.z = speedToCompare;
	}
	else if (moveVel.z < -speedToCompare)
	{
		moveVel.z = -speedToCompare;
	}
}

//could optimise this by changing collision so that it takes a reference to a vector which it sets, then use the output vector to set respective vectors (eliminates the need for the addition then the subtraction)
void Character::adjustPosition()
{
	velocity += moveVel; //need vel to have moveVel for collision to work properly (needs to set both moveVel and vel to 0 in case of collision)

	for (auto polyhedron : globals::polyhedrons)
	{
		collisionDetection::correctPolyhedrons(this, &polyhedron);
	}

	position += velocity * glm::vec3{ -1, 1, 1 };

	//reset vel to keep vel and moveVel separate (but only if it didn't collide with something that set it to zero)
	if (velocity.x != 0)
	{
		velocity.x -= moveVel.x;
	}
	if (velocity.z != 0)
	{
		velocity.z -= moveVel.z;
	}

	setVkObjectPosition(position);
}
