#include "Globals.h"
#include "Character.h"
#include "Cube.h"
#include "Platform.h"

#include <windows.h>
#include <chrono>

//for testing
#include <thread>

using std::chrono::time_point_cast;
using std::chrono::duration_cast;

const bool debug = false;

int main()
{
	using std::make_shared;

	try
	{
		typedef std::chrono::high_resolution_clock Time;
		typedef std::chrono::microseconds us;

		globals::globalInit();

		auto player1 = make_shared<Character>(glm::vec3(1, 1, 1) * 0.2f, glm::vec3(0, 4, 0), 60);
		player1->name = "player1";
		globals::polyhedrons.push_back(player1);
		
		auto player2 = make_shared<Character>(glm::vec3(1, 1, 1) * 0.2f, glm::vec3(0, 4, 0), 60);
		player2->name = "player2";
		player2->controlScheme.forward = &globals::input.keys.keyCounts["upArrow"];
		player2->controlScheme.backward = &globals::input.keys.keyCounts["downArrow"];
		player2->controlScheme.left = &globals::input.keys.keyCounts["leftArrow"];
		player2->controlScheme.right = &globals::input.keys.keyCounts["rightArrow"];
		player2->controlScheme.jump = &globals::input.keys.keyCounts["rightShift"];
		globals::polyhedrons.push_back(player2);

		auto currentTime = time_point_cast<us>(Time::now());
		double accumulator = 0.0;

		glm::vec3 cameraOffset{ 0, 2, 0 };

		while (!globals::gfx.shouldClose) {
			auto newTime = time_point_cast<us>(Time::now());
			auto frameTime = duration_cast<us>(newTime - currentTime).count();
			currentTime = newTime;

			accumulator += frameTime;

			while (accumulator >= globals::dt)
			{
				globals::gfx.setCameraAngle(globals::input.cameraAngle);
				globals::input.run();

				for (auto polyhedron : globals::polyhedrons)
				{
					polyhedron->perLoop();
				}

				globals::gfx.setCameraPos(player1->position + cameraOffset);

				if (globals::input.keys.keyCounts["f"] == 1)
				{
					globals::polyhedrons.push_back(make_shared<Cube>(1, glm::vec3(player1->position.x, player1->position.y, player1->position.z), 100));
				}

				if (globals::input.keys.keyCounts["leftCtrl"] == 1)
				{
					globals::gfx.setObjectsWireFrame(true);
				}
				else if (globals::input.keys.keyCounts["leftCtrl"] == 0)
				{
					globals::gfx.setObjectsWireFrame(false);
				}

				accumulator -= globals::dt;
			}

			globals::gfx.run();
		}
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		for (int i = 0; i < 100000000; i++) {}
		return EXIT_FAILURE;
	}

	globals::gfx.cleanup();

	return EXIT_SUCCESS;
}