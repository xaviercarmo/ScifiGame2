#pragma once
#include "Globals.h"

class Character :
	public Polyhedron
{
public:
	explicit Character(glm::vec3 dimensions, glm::vec3 position, float mass);

	void jump();

	void receiveInput();

private:
	int health = 100;
	double moveSpeed = 0.5;
	float moveForce = 50;
	float jumpForce = mass * -globals::gravityAccel * 15;
};