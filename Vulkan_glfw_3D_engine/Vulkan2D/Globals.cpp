#include "Globals.h"
#include "Cube.h"

namespace globals
{
	Graphics gfx;
	Input input;

	const float dt = 1000.0f / 60.0f;
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
			Cube{ glm::vec3(1, 1, 1), glm::vec3(1.6, 0, 0), 100 },
			Cube{ glm::vec3(1, 1, 1), glm::vec3(3.2, 0, 0), 100 },
			Cube{ glm::vec3(1, 1, 1), glm::vec3(4.8, 0, 0), 100 },
			Cube{ glm::vec3(1, 1, 1), glm::vec3(6.4, 0, 0), 100 },
			Cube{ glm::vec3(1, 1, 1), glm::vec3(8, 0, 0), 100 },
			Cube{ glm::vec3(1, 1, 1), glm::vec3(9.6, 0, 0), 100 },
			Cube{ glm::vec3(1, 1, 1), glm::vec3(11.2, 0, 0), 100 },
			Cube{ glm::vec3(1, 1, 1), glm::vec3(12.8, 0, 0), 100 },
			Cube{ glm::vec3(1, 1, 1), glm::vec3(14.4, 0, 0), 100 }
		};
	}
}