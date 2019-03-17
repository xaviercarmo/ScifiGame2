#include "Graphics.h"
#include "Input.h"
#include "Polyhedron.h"

namespace globals
{
	extern Graphics gfx;
	extern Input input;

	extern const double dt;
	extern const float dtSeconds;

	extern float gravityAccel;

	extern std::vector<Polyhedron> polyhedrons;

	void globalInit();
}