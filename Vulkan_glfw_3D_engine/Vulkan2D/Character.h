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
	float maxMoveSpeedAir = 0.05;
	float moveForceGround = 80;
	float moveForceAir = 40;
	float diagMoveForce = moveForceGround * 0.7;
	float jumpForce = mass * -globals::gravityAccel * 15;

	glm::vec3 moveVel{ 0, 0, 0 };
	glm::vec3 moveForceVec{ 0, 0, 0 };

	void limitMoveVel();
	void adjustPosition();

	void handleContactionFriction();
	void handleContactFrictionFlips();
};