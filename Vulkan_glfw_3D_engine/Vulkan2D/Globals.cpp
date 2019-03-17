#include "Globals.h"
#include "Cube.h"

namespace globals
{
	Graphics gfx;
	Input input;

	const double dt = 1000.0 / 60.0;
	const float dtSeconds = dt / 1000.0f;

	float gravityAccel = -0.98f;
	std::vector<Polyhedron> polyhedrons;
	
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		globals::input.key_callback(key, scancode, action, mods);
	}

	void globalInit()
	{
		gfx.init();
		input.init(globals::gfx.getWindowPointer());
		glfwSetKeyCallback(globals::gfx.getWindowPointer(), key_callback);

		polyhedrons = std::vector<Polyhedron>
		{
			Cube{ glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), 100 },
			Cube{ glm::vec3(1, 1, 1), glm::vec3(1.2, 0, 0), 100 },
			Cube{ glm::vec3(1, 1, 1), glm::vec3(2.4, 0, 0), 100 },
			Cube{ glm::vec3(1, 1, 1), glm::vec3(3.6, 0, 0), 100 },
			Cube{ glm::vec3(1, 1, 1), glm::vec3(4.8, 0, 0), 100 },
			Cube{ glm::vec3(1, 1, 1), glm::vec3(6, 0, 0), 100 },
			Cube{ glm::vec3(1, 1, 1), glm::vec3(7.2, 0, 0), 100 },
			Cube{ glm::vec3(1, 1, 1), glm::vec3(8.4, 0, 0), 100 },
			Cube{ glm::vec3(1, 1, 1), glm::vec3(9.6, 0, 0), 100 },
			Cube{ glm::vec3(1, 1, 1), glm::vec3(10.8, 0, 0), 100 }
		};
	}

}