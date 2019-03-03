#include "Graphics.h"
#include "Input.h"
#include "CollisionDetection.h"
#include <ctime>
#include <windows.h>
#include <chrono>

Graphics gfx;
Input input;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	input.key_callback(key, scancode, action, mods);
}

int main() {
	try {

		gfx.init();
		input.init(gfx.getWindowPointer());
		glfwSetKeyCallback(gfx.getWindowPointer(), key_callback);
		bool lastF;
		std::vector<CollisionBox> boxes;
		CollisionBox test;
		test.dimensions = glm::vec3(1, 1, 1);
		test.velocity = glm::vec3(0, 0, 0);
		test.position = glm::vec3(0, 0, 0);
		boxes.push_back(test);
		glm::vec3 inputVelocity = glm::vec3(0, 0, 0);
		CollisionBox camera;
		camera.dimensions = glm::vec3(0.01, 0.01, 0.01);
		camera.velocity = glm::vec3(0, 0, 0);
		bool lastSpace;

		//time_t startTime;
		//time_t endTime;

		//int frameTimeTarged = 1000 / 60;

		//start further test variables for new framerate method

		double t = 0.0;
		const double dt = 1000.0 / 60.0; //1.0 / 60.0;
		float accel = 0;

		auto currentTime = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now());
		double accumulator = 0.0;

		//end new test variables
		int counter = 0;
		while (!gfx.shouldClose) {
			//startTime = time(NULL);
			auto newTime = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()); //gets the current time in seconds
			auto frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(newTime - currentTime); //gets the elapsed time in seconds
			currentTime = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now());

			accumulator += frameTime.count();

			while (accumulator >= dt) { //while we have more than one frames-worth of time, use it
				counter++;
				printf("counter, accumulator, dt: %d, %f, %f\n", counter, accumulator, dt);
				gfx.setCameraAngle(input.cameraAngle);
				input.run();
				inputVelocity = glm::vec3(0, 0, 0);

				double standardVel = 1.0 / 100.0;
				if (input.keys.w) {
					inputVelocity.z += standardVel; //player should move at 1m/s, this gets executed 60 times per second in theory, so 1/60m/s
				}
				if (input.keys.a) {
					inputVelocity.x += -standardVel;
				}
				if (input.keys.s) {
					inputVelocity.z += -standardVel;
				}
				if (input.keys.d) {
					inputVelocity.x += standardVel;
				}
				if (input.keys.space) {
					inputVelocity.y += standardVel;
				}
				if (input.keys.leftShift) {
					inputVelocity.y += -standardVel;
				}
				//need to do these above movements using integrate() with our own integration method, he describe a couple but simplistic euler looks the best for performance/accuracy balance

				camera.velocity = gfx.getProperCameraVelocity(inputVelocity);
				camera.velocity += accel * dt;
				for (int i = 0; i < boxes.size(); i++) {
					collisionDetection::correctCollisionBoxes(&camera, &boxes[i]);
				}

				camera.position += camera.velocity * (float)dt;
				gfx.setCameraPos(camera.position);
				if (input.keys.f && !lastF) {
					gfx.addObject(gfx.getCameraPos().x, gfx.getCameraPos().y, gfx.getCameraPos().z, 1);
					test.dimensions = glm::vec3(1, 1, 1);
					test.velocity = glm::vec3(0, 0, 0);
					test.position = glm::vec3(gfx.getCameraPos().x, gfx.getCameraPos().y, gfx.getCameraPos().z);
					boxes.push_back(test);
				}
				lastF = input.keys.f;

				accumulator -= dt;
				t += dt;

				gfx.run();
				//endTime = time(NULL);
				//Sleep(frameTimeTarged - (endTime - startTime));
			}
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