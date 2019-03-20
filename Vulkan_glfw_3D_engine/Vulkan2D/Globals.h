#include "Polyhedron.h"
#include "Input.h"

namespace globals
{
	extern Graphics gfx;
	extern Input input;

	extern const float dt;
	extern const float dtSeconds;

	extern float gravityAccel;

	extern std::vector<Polyhedron> polyhedrons;

	void globalInit();
}