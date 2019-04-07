#pragma once
#include "Polyhedron.h"
class Cube :
	public Polyhedron
{
public:
	explicit Cube(float size, glm::vec3 position, float mass, bool stationary = true);

	void perLoop(); // override;
};

