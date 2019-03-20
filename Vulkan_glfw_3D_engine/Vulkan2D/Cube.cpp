#include "Cube.h"
#include "Globals.h"

Cube::Cube(glm::vec3 dimensions, glm::vec3 position, float mass) : Polyhedron(dimensions, position, mass, true)
{
	//vkObject = globals::gfx.addObject(position.x, position.y, position.z, 1);
	vkObjectIndex = globals::gfx.addObject(position.x, position.y, position.z, 1);
}