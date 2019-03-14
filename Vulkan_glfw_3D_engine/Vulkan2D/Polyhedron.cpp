#include "Polyhedron.h"
#include "CollisionDetection.h"

//adds accel to vel, adjusts vel and pos base on collision, then adds remaining vel to pos
void Polyhedron::applyPhysics(float dt, std::vector<Polyhedron>& polyhedrons)
{
	//acceleration *= dt; //clearer but less concise
	velocity += acceleration * dt;
	velocity *= glm::vec3(-1 * dt, dt, dt) * 0.5f;

	for (auto polyhedron : polyhedrons)
	{
		collisionDetection::correctPolyhedrons(this, &polyhedron);
	}

	position += velocity;
}
