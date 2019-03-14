#include "Graphics.h"
#include "Character.h"
#include "Polyhedron.h"
#include <ctime>
#include <windows.h>
#include <chrono>

Graphics gfx;
Input input;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	input.key_callback(key, scancode, action, mods);
}

const bool debug = false;

int main() {
	try {

		gfx.init();
		input.init(gfx.getWindowPointer());
		glfwSetKeyCallback(gfx.getWindowPointer(), key_callback);

		bool lastF;
		std::vector<Polyhedron> polyhedrons;
		Polyhedron test(glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), true); //later implement cube class which is child of polyhedron, these are all cubes
		polyhedrons.push_back(test);

		Character player1(glm::vec3(0.01, 0.01, 0.01), glm::vec3(0, 0, 0));

		double t = 0.0;
		const float dt = 1000.0f / 60.0f;

		auto currentTime = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now());
		double accumulator = 0.0;

		int counter = 0;
		while (!gfx.shouldClose) {
			auto newTime = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()); //gets the current time in seconds
			auto frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(newTime - currentTime); //gets the elapsed time in seconds
			currentTime = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now());

			accumulator += frameTime.count();

			while (accumulator >= dt) {
				counter++;

				if (debug) {
					printf("counter, accumulator, dt: %d, %f, %f\n", counter, accumulator, dt);
				}

				gfx.setCameraAngle(input.cameraAngle);
				input.run();

				player1.receiveInput(input.keys, gfx);
				player1.applyPhysics(dt, polyhedrons);
				
				gfx.setCameraPos(player1.position);
				if (input.keys.f && !lastF) {
					gfx.addObject(gfx.getCameraPos().x, gfx.getCameraPos().y, gfx.getCameraPos().z, 1);
					polyhedrons.push_back(Polyhedron(glm::vec3(1, 1, 1), glm::vec3(gfx.getCameraPos().x, gfx.getCameraPos().y, gfx.getCameraPos().z), true)); //change this to push_back(Polyhedron(...)), unless addObject linked to test somehow
				}
				lastF = input.keys.f;

				accumulator -= dt;
				t += dt;
			}

			gfx.run();
		}
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		for (int i = 0; i < 100000000; i++) {}
		return EXIT_FAILURE;
	}
	gfx.cleanup();
	return EXIT_SUCCESS;
}