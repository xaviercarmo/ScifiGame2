#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

#include <vector>

namespace Physics {
	struct ObjectState
	{
		float x;
		float y;
		float z;

		float vel;
	};

	struct ObjectStateDerivative
	{
		float dx;
		float dy;
		float dz;

		float dvel;
	};

	class Engine
	{
	public:
		float gravity = 9.8f;

		ObjectStateDerivative evaluate(const ObjectState & initial, double t, float dt, const ObjectStateDerivative & d);
		float acceleration(const ObjectState& state, double t);
		void integrate(ObjectState & state, double t, float dt);
	};
}