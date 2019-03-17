#pragma once
#include "Polyhedron.h"
class Cube :
	public Polyhedron
{
public:
	explicit Cube(glm::vec3 dimensions, glm::vec3 position, float mass);
};

