#include "InputManager.h"
#include "iostream"
#include "thread"

int InputManager::up= 0;
int InputManager::right = 0;
int InputManager::forward = 0;
bool InputManager::stopThreads = false;

void InputManager::parallel_loop1()
{
	while (true) {
		
		if (glfwGetKey(window, GLFW_KEY_W) == 1)
			this->up = 1;
		else if (glfwGetKey(window, GLFW_KEY_S) == 1)
			this->up = -1;
		else
		{
			this->up = 0;
		}
	}
}

void InputManager::parallel_loop2()
{
	while (true) {
		if (glfwGetKey(window, GLFW_KEY_D) == 1)
			this->right = 1;
		else if (glfwGetKey(window, GLFW_KEY_A) == 1)
			this->right = -1;

		else {
			this->right = 0;
		}
	}
}

InputManager::InputManager(GLFWwindow* window)
{
	this->window = window;
	fetch_inputs();
}
InputManager::~InputManager()
{
	stopThreads = true;
}

void InputManager::fetch_inputs()
{
	stopThreads = false;
	std::thread thread1(&InputManager::parallel_loop1, this);
	std::thread thread2(&InputManager::parallel_loop2, this);

	thread1.detach();
	thread2.detach();

	//???not safe
}
