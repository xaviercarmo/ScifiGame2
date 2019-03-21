#include "Globals.h"
#include "Character.h"
#include "Cube.h"

#include <windows.h>
#include <chrono>

using std::chrono::time_point_cast;
using std::chrono::duration_cast;

const bool debug = false;

int main() {
	try {
		typedef std::chrono::high_resolution_clock Time;
		typedef std::chrono::milliseconds ms;

		globals::globalInit();

		bool lastF;

		//Character player1(glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.5, 2, 0.5), 60);
		Character player1(glm::vec3(1, 1, 1) * 0.2f, glm::vec3(0, 4, 0), 60);

		double t = 0.0;
		auto currentTime = time_point_cast<ms>(Time::now());
		double accumulator = 0.0;
		
		glm::vec3 cameraOffset{ 0, 2, 0 };

		while (!globals::gfx.shouldClose) {
			auto newTime = time_point_cast<ms>(Time::now());
			auto frameTime = duration_cast<ms>(newTime - currentTime);
			currentTime = newTime;

			accumulator += frameTime.count();

			while (accumulator >= globals::dt) {
				globals::gfx.setCameraAngle(globals::input.cameraAngle);
				globals::input.run();

				player1.receiveInput();
				player1.applyPhysics();
				
				globals::gfx.setCameraPos(player1.position + cameraOffset);
				if (globals::input.keys.f && !lastF) {
					globals::polyhedrons.push_back(Cube(glm::vec3(1, 1, 1), glm::vec3(player1.position.x, player1.position.y, player1.position.z), 100));
				}
				lastF = globals::input.keys.f;

				accumulator -= globals::dt;
				t += globals::dt;
			}

			globals::gfx.run();
		}
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		for (int i = 0; i < 100000000; i++) {}
		return EXIT_FAILURE;
	}
	globals::gfx.cleanup();
	return EXIT_SUCCESS;
}