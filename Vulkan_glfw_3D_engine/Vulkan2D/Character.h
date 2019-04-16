#pragma once
#include "Globals.h"

struct ControlScheme
{
	int* forward;
	int* backward;
	int* left;
	int* right;
	int* jump;
};

class Character :
	public Polyhedron
{
public:
	explicit Character(glm::vec3 dimensions, glm::vec3 position, float mass);

	void receiveInput();
	void perLoop() override;

	ControlScheme controlScheme{ &globals::input.keys.keyCounts["w"], &globals::input.keys.keyCounts["s"], &globals::input.keys.keyCounts["a"], &globals::input.keys.keyCounts["d"], &globals::input.keys.keyCounts["space"] };

private:
	int health = 100;
	float maxMoveSpeedGround = 0.1f;
	float moveForceGround = 80;
	float moveForceAir = 8;
	float diagMoveForceGround = moveForceGround * 0.7f;
	float diagMoveForceAir = moveForceAir * 0.7f;
	float jumpForce = 900;

	bool spacePressed = false;
	bool canSlam = false;

	glm::vec3 moveVel{ 0, 0, 0 };
	glm::vec3 moveForceVec{ 0, 0, 0 };

	void jump();
	void slam();
	void applyPhysics();
	void limitMoveVel();
	void adjustPosition();
};