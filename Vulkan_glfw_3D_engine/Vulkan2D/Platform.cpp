#include "Platform.h"
#include "Globals.h"

Platform::Platform(glm::vec3 dimensions, glm::vec3 position, float mass) : Polyhedron(dimensions, position, mass, true)
{
	vkObjectIndex = globals::gfx.addObject(position.x, position.y, position.z, 4);
}