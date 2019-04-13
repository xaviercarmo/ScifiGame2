#pragma once
#include "Globals.h"

struct ControlScheme
{
	bool* forward;
	bool* backward;
	bool* left;
	bool* right;
	bool* jump;
};

class Character :
	public Polyhedron
{
public:
	explicit Character(glm::vec3 dimensions, glm::vec3 position, float mass);

	void jump();
	void applyPhysics();
	void receiveInput();
	void perLoop();// override;

	ControlScheme controlScheme{ &globals::input.keys.w, &globals::input.keys.s, &globals::input.keys.a, &globals::input.keys.d, &globals::input.keys.space };

private:
	int health = 100;
	float maxMoveSpeedGround = 0.1f;
	float moveForceGround = 80;
	float moveForceAir = 8;
	float diagMoveForceGround = moveForceGround * 0.7f;
	float diagMoveForceAir = moveForceAir * 0.7f;
	float jumpForce = 900;

	glm::vec3 moveVel{ 0, 0, 0 };
	glm::vec3 moveForceVec{ 0, 0, 0 };

	void limitMoveVel();
	void adjustPosition();
};