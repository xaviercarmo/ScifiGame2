#pragma once
#include <glm/glm.hpp>
#include <vector>


class Polyhedron
{
public:
	glm::vec3 dimensions{ 0, 0, 0 };
	glm::vec3 position{ 0, 0, 0 };
	glm::vec3 velocity{ 0, 0, 0 };
	glm::vec3 acceleration{ 0, 0, 0 };
	bool stationary = true;

	explicit Polyhedron(glm::vec3 dimensions, glm::vec3 position, bool stationary) : dimensions(dimensions), position(position), stationary(stationary)
	{}

	//Apply physics function, in main loop should iterate all polyhedrons and call this method 
	void applyPhysics(float dt, std::vector<Polyhedron>& polyhedrons);
};

