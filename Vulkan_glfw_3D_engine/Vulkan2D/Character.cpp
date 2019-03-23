#include "Character.h"
#include "CollisionDetection.h"

Character::Character(glm::vec3 dimensions, glm::vec3 position, float mass) : Polyhedron(dimensions, position, mass, false)
{
	vkObjectIndex = globals::gfx.addObject(position.x, position.y, position.z, 0);

	setStaticFrictionConstant(0.9f);
	setKineticFrictionConstant(0.8f);
	moveForce = 60;
}

void Character::receiveInput()
{
	if (globals::input.keys.w && baseInContact())
	{
		force.z += moveForce;
	}

	if (globals::input.keys.a && baseInContact())
	{
		force.x += -moveForce;
	}

	if (globals::input.keys.s && baseInContact())
	{
		force.z += -moveForce;
	}

	if (globals::input.keys.d && baseInContact())
	{
		force.x += moveForce;
	}

	if (globals::input.keys.space && baseInContact())
	{
		jump();
	}

	if (globals::input.keys.leftShift)
	{
		force *= 0;
		velocity *= 0;
		position = glm::vec3{ 0.5, 2, 0.5 };
		setVkObjectPosition(position);
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
	force.y += jumpForce;
}