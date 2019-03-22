#pragma once
#include "Polyhedron.h"
class Platform :
	public Polyhedron
{
public:
	explicit Platform(glm::vec3 dimensions, glm::vec3 position, float mass);
};
