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

	float kineticFrictionConstant = 0.6;
	float staticFrictionConstant = 0.8;

	float positiveStaticFrictionForce = 0;
	float positiveKineticFrictionForce = 0;

	glm::vec3 flippedDirections{ false, false, false };

	glm::vec3 velocityTransform{ 0, 0, 0 };
	glm::vec3 accelerationTransform{ 0, 0, 0 };

	bool stationary = true;

	explicit Polyhedron(glm::vec3 dimensions, glm::vec3 position, float mass, bool stationary);

	void applyPhysics();

	void setPositiveStaticFrictionForce();
	void setPositiveKineticFrictionForce();

	glm::vec3 getVecDirections(glm::vec3 vec);

	void applyContactFriction(float velocity, int direction, float& force);
	void handleFrictionFlip(float& velocity, int oldDirection, int newDirection, float force);
};