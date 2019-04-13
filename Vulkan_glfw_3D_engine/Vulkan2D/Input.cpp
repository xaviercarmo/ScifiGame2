#include "Input.h"
#include <iostream>

void Input::init(GLFWwindow * window)
{
	windowPointer = window;
}
//======================================================================||
// function that uses glfw to get key inputs (presses and releases) and ||
// uses them to set the KeyValues struct's properties, so that anywhere ||
// I to know what keys are pressed, I can just find out using the       ||
// keyValues struct.                                                    ||
//======================================================================||

void Input::run() {
	glfwPollEvents();
	glfwGetCursorPos(windowPointer, &xpos, &ypos);
	if (inFocus) {

		glfwSetCursorPos(windowPointer, windowWidth / 2, windowHeight / 2);
		cameraAngle.x += 0.003 * float(windowWidth / 2 - xpos);
		cameraAngle.y += 0.003 * float(windowHeight / 2 - ypos);
		if (cameraAngle.y < -3.14 / 2) {
			cameraAngle.y = -3.14 / 2;
		}
		if (cameraAngle.y > 3.14 / 2) {
			cameraAngle.y = 3.14 / 2;
		}
		glfwSetInputMode(windowPointer, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
	else {
		glfwSetInputMode(windowPointer, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	glfwGetFramebufferSize(windowPointer, &windowWidth, &windowHeight);
	mousePosInWindow = glm::vec2(2 * (xpos - windowWidth / 2), 2 * (ypos - windowHeight / 2));
}

void Input::clearInputString() {
	inputString = "";
}
//Callback function for scrolling with the mouse
void Input::scroll_callback(double xoffset, double yoffset)
{
	if (yoffset != 0) {
		mouseScrollValue = yoffset;
	}
}
//Callback function for all keyboard input
void Input::key_callback(int key, int scancode, int action, int mods)
{
	//Code for allowing the user to type out strings (for a textbox)
	if (stringInputEnabled) {
		if (action == GLFW_PRESS) {
			if (key == GLFW_KEY_A ||
				key == GLFW_KEY_B ||
				key == GLFW_KEY_C ||
				key == GLFW_KEY_D ||
				key == GLFW_KEY_E ||
				key == GLFW_KEY_F ||
				key == GLFW_KEY_G ||
				key == GLFW_KEY_H ||
				key == GLFW_KEY_I ||
				key == GLFW_KEY_J ||
				key == GLFW_KEY_K ||
				key == GLFW_KEY_L ||
				key == GLFW_KEY_M ||
				key == GLFW_KEY_N ||
				key == GLFW_KEY_O ||
				key == GLFW_KEY_P ||
				key == GLFW_KEY_Q ||
				key == GLFW_KEY_R ||
				key == GLFW_KEY_S ||
				key == GLFW_KEY_T ||
				key == GLFW_KEY_U ||
				key == GLFW_KEY_V ||
				key == GLFW_KEY_W ||
				key == GLFW_KEY_X ||
				key == GLFW_KEY_Y ||
				key == GLFW_KEY_Z ||
				key == GLFW_KEY_1 ||
				key == GLFW_KEY_2 ||
				key == GLFW_KEY_3 ||
				key == GLFW_KEY_4 ||
				key == GLFW_KEY_5 ||
				key == GLFW_KEY_6 ||
				key == GLFW_KEY_7 ||
				key == GLFW_KEY_8 ||
				key == GLFW_KEY_9 ||
				key == GLFW_KEY_0 ||
				key == GLFW_KEY_MINUS
				) {
				if (keys.leftShift || keys.rightShift) {
					if (key == GLFW_KEY_MINUS) {
						inputString += "_";
					}
					else {
						inputString += glfwGetKeyName(key, 0)[0];
					}
				}
				else {
					if (glfwGetKeyName(key, 0)[0] > 64) {
						inputString += glfwGetKeyName(key, 0)[0] + 32;
					}
					else {
						if (key == GLFW_KEY_MINUS) {
							inputString += "-";
						}
						else {
							inputString += glfwGetKeyName(key, 0)[0];
						}
					}
				}
			}
			if (key == GLFW_KEY_SPACE) {
				inputString += " ";
			}
			if (key == GLFW_KEY_BACKSPACE && inputString.size() > 0) {
				inputString.resize(inputString.size() - 1);
				if (keys.leftCtrl) {
					inputString = "";
				}
			}
		}
	}

	switch (key)
	{
		case GLFW_KEY_1:
			keys.n1 = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_2:
			keys.n2 = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_3:
			keys.n3 = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_4:
			keys.n4 = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_5:
			keys.n5 = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_6:
			keys.n6 = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_7:
			keys.n7 = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_8:
			keys.n8 = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_9:
			keys.n9 = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_0:
			keys.n0 = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_LEFT_ALT:
			keys.leftAlt = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_ESCAPE:
			keys.escape = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_SPACE:
			keys.space = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_LEFT_SHIFT:
			keys.leftShift = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_RIGHT_SHIFT:
			keys.rightShift = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_LEFT_CONTROL:
			keys.leftCtrl = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_TAB:
			keys.tab = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_LEFT:
			keys.leftArrow = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_RIGHT:
			keys.rightArrow = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_UP:
			keys.upArrow = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_DOWN:
			keys.downArrow = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_A:
			keys.a = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_B:
			keys.b = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_C:
			keys.c = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_D:
			keys.d = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_E:
			keys.e = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_F:
			keys.f = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_G:
			keys.g = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_H:
			keys.h = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_I:
			keys.i = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_J:
			keys.j = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_K:
			keys.k = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_L:
			keys.l = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_M:
			keys.m = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_N:
			keys.n = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_O:
			keys.o = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_P:
			keys.p = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_Q:
			keys.q = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_R:
			keys.r = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_S:
			keys.s = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_T:
			keys.t = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_U:
			keys.u = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_V:
			keys.v = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_W:
			keys.w = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_X:
			keys.x = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_Y:
			keys.y = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_KEY_Z:
			keys.z = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
	}
}
//Callback function for mouse click input
void Input::mouse_button_callback(int button, int action, int mods)
{
	switch (button)
	{
		case GLFW_MOUSE_BUTTON_LEFT:
			keys.mouseLeft = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			keys.mouseRight = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			keys.mouseMiddle = action & (GLFW_PRESS | GLFW_REPEAT);
			break;
	}
}

//Another callback, this time for detecting whether or not the window is in focus
void Input::window_focus_callback(int focused)
{
	if (focused)
	{
		inFocus = true;
	}
	else
	{
		inFocus = false;
	}
}