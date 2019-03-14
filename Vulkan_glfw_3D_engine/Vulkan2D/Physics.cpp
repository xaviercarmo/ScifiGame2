#include "Physics.h"


namespace Physics
{
	ObjectStateDerivative Engine::evaluate(const ObjectState & initial, double t, float dt, const ObjectStateDerivative & d)
	{
		return ObjectStateDerivative();
	}

	float Engine::acceleration(const ObjectState & state, double t)
	{
		return 0.0f;
	}

	void Engine::integrate(ObjectState & state, double t, float dt)
	{
		/*state.vel += acceleration(state, t) * dt;
		position += velocity * dt;*/
	}
}