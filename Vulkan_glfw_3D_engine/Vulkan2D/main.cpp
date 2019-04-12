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
	try
	{
		typedef std::chrono::high_resolution_clock Time;
		typedef std::chrono::microseconds us;

		globals::globalInit();

		bool lastF;

		Character player1(glm::vec3(1, 1, 1) * 0.2f, glm::vec3(0, 4, 0), 60);

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

				player1.perLoop();

				globals::gfx.setCameraPos(player1.position + cameraOffset);

				if (globals::input.keys.f && !lastF)
				{
					globals::polyhedrons.push_back(Cube(1, glm::vec3(player1.position.x, player1.position.y, player1.position.z), 100));
				}
				lastF = globals::input.keys.f;

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