#include "Character.h"

void Character::receiveInput(keyValues inputKeys, Graphics& gfx)
{
	resetVel();

	if (inputKeys.w) {
		velocity.z += moveSpeed;
	}
	if (inputKeys.a) {
		velocity.x += -moveSpeed;
	}
	if (inputKeys.s) {
		velocity.z += -moveSpeed;
	}
	if (inputKeys.d) {
		velocity.x += moveSpeed;
	}
	if (inputKeys.space) {
		velocity.y += moveSpeed;
	}
	if (inputKeys.leftShift) {
		velocity.y += -moveSpeed;
	}
	if (inputKeys.alt) {
		gfx.setFreeLook(true);
	}
	else {
		gfx.setFreeLook(false);
		gfx.setCameraAngle(glm::vec3(0, -1, 1));
	}
}

void Character::jump()
{
	//velocity.y = 
}

void Character::resetVel()
{
	velocity *= 0;
}
