#include "Globals.h"
#include "Cube.h"
#include "platform.h"
namespace globals
{
	Graphics gfx;
	Input input;

	const float dt = 1000000.0f / 60.0f;
	const float dtSeconds = 1.0f / 60.0f;

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
			Platform{ glm::vec3(100, 1, 100), glm::vec3(-50, -5, -50), 100 },
			//Cube{ 1.0f, glm::vec3(), 50},
			/*Cube{ 1.0f, glm::vec3(0.00, 0, 0), 100 },
			Cube{ 1.0f, glm::vec3(1.60, 0, 0), 100 },
			Cube{ 1.0f, glm::vec3(3.20, 0, 0), 100 },
			Cube{ 1.0f, glm::vec3(4.80, 0, 0), 100 },
			Cube{ 1.0f, glm::vec3(6.40, 0, 0), 100 },
			Cube{ 1.0f, glm::vec3(8.00, 0, 0), 100 },
			Cube{ 1.0f, glm::vec3(9.60, 0, 0), 100 },
			Cube{ 1.0f, glm::vec3(11.2, 0, 0), 100 },
			Cube{ 1.0f, glm::vec3(12.8, 0, 0), 100 },
			Cube{ 1.0f, glm::vec3(14.4, 0, 0), 100 },
			Platform{ glm::vec3(15.4, 0.2, 1), glm::vec3(0, -0.2, 0), 100 }*/
		};
		polyhedrons.push_back(Platform{ glm::vec3(10, 1.785, 10), glm::vec3(-50 + 5 * 10, -4, -50 + 5 * 10), 100 });
		/*int k = 0;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				k++;

				if (k % 2 == 0)
				{
					polyhedrons.push_back(Platform{ glm::vec3(10, 1.5, 10), glm::vec3(-50 + i * 10, -4, -50 + j * 10), 100 });
				}
			}
			k++;
		}*/
	}
}