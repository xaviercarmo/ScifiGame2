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
	glm::vec3 force{ 0, 0, 0 };
	float mass;

	float positiveStaticFrictionForce = 0.0;
	float positiveKineticFrictionForce = 0.0;

	glm::vec3 flippedDirections{ false, false, false };

	bool stationary = true;

	explicit Polyhedron(glm::vec3 dimensions, glm::vec3 position, float mass, bool stationary);

	void applyPhysics();

	void setStaticFrictionConstant(float newVal);
	void setKineticFrictionConstant(float newVal);

	glm::vec3 getVecDirections(glm::vec3 vec);

	void applyContactFriction(float velocity, int direction, float& force);
	void handleFrictionFlip(float& velocity, int oldDirection, int newDirection, float force);
protected:
	float kineticFrictionConstant;
	float staticFrictionConstant;
};