#pragma once
#include "keycodes.h"
#include "future"
#include "GLFW/glfw3.h"

class InputManager {

	static int up;
	static int right;
	static int forward;

	static bool stopThreads;
	GLFWwindow* window;

	void parallel_loop1();
	void parallel_loop2();



public :

	InputManager(GLFWwindow* window);
	~InputManager();


	void fetch_inputs();
	inline int getAxisX() { return right; };
	inline int getAxisY() { return up; };
	inline int getAxisZ() { return forward; };
	
};
