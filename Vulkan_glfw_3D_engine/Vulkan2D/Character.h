#pragma once
#include "Polyhedron.h"
#include "Graphics.h"
#include "Input.h"

class Character: public Polyhedron {
public:
	//character traits (think enemies can be extensions of character
	//... more later, not necessary now

	//constructor
	explicit Character(glm::vec3 dimensions, glm::vec3 position) : Polyhedron(dimensions, position, false)
	{}

	void jump();

	void receiveInput(keyValues inputKeys, Graphics& gfx);

	void resetVel();
private:
	int health = 100;
	float moveSpeed = 1.0f / 100.0f;
	//... more later, not necessary now
};