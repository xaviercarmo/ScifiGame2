#pragma once

#include <GLFW\glfw3.h>
#include <string>
#include <glm\glm.hpp>

struct KeyValues
{
	bool 
		a = false,
		b = false,
		c = false,
		d = false,
		e = false,
		f = false,
		g = false,
		h = false,
		i = false,
		j = false,
		k = false,
		l = false,
		m = false,
		n = false,
		o = false,
		p = false,
		q = false,
		r = false,
		s = false,
		t = false,
		u = false,
		v = false,
		w = false,
		x = false,
		y = false,
		z = false,
		leftShift = false,
		rightShift = false,
		space = false,
		leftCtrl = false,
		tab = false,
		n1 = false,
		n2 = false,
		n3 = false,
		n4 = false,
		n5 = false,
		n6 = false,
		n7 = false,
		n8 = false,
		n9 = false,
		n0 = false,
		mouseLeft = false,
		mouseRight = false,
		mouseMiddle = false,
		escape = false,
		leftAlt = false;
};

class Input {
public:
	std::string inputString = "";
	KeyValues keys;
	//int mouseScrollValue = 0;
	bool stringInputEnabled = true;
	bool EXIT = false;
	void run();
	double xpos, ypos;
	glm::vec3 cameraAngle = glm::vec3(0, 0, 0);
	int windowWidth, windowHeight;
	glm::vec2 mousePosInWindow;
	void init(GLFWwindow* window);
	GLFWwindow* windowPointer;
	void clearInputString();
	void scroll_callback(double xoffset, double yoffset);
	void key_callback(int key, int scancode, int action, int mods);
	void mouse_button_callback(int button, int action, int mods);
	bool inFocus = true;
	void window_focus_callback(int focused);
private:
	int mouseScrollValue = 0;
};
