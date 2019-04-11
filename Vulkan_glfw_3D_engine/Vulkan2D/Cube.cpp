#include "Cube.h"
#include "Globals.h"

Cube::Cube(float size, glm::vec3 position, float mass, bool stationary) : Polyhedron(glm::vec3{ size, size, size }, position, mass, stationary)
{
	vkObjectIndex = globals::gfx.addObject(position, glm::vec3(1,1,1), 1);
}

//void Cube::perLoop()
//{
//}
