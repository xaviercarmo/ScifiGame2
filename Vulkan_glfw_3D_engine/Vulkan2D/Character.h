#pragma once
#include "Globals.h"

class Character :
	public Polyhedron
{
public:
	explicit Character(glm::vec3 dimensions, glm::vec3 position, float mass);

	void jump();
	void applyPhysics();
	void receiveInput();
	void perLoop();

private:
	int health = 100;
	float maxMoveSpeedGround = 0.1;
	float moveForceGround = 80;
	float moveForceAir = 8;
	float diagMoveForceGround = moveForceGround * 0.7;
	float diagMoveForceAir = moveForceAir * 0.7;
	float jumpForce = 900;

	glm::vec3 moveVel{ 0, 0, 0 };
	glm::vec3 moveForceVec{ 0, 0, 0 };

	void limitMoveVel();
	void adjustPosition();
};