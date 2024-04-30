#pragma once
#include "Renderer.h"
#include "Entity.h"
#include "GLFW/glfw3.h"

#ifndef W_HEIGHT
	#define W_HEIGHT 768
#endif
#ifndef W_WIDTH
	#define W_WIDTH 1366
#endif
#ifndef WORLD_LENGTH
	#define WORLD_LENGTH 10000
#endif

#define GOOF_MODE_3D 0
#define GOOF_MODE_2D 1

#include <iostream>
#include "Camera.h"

class _Window {

		GLFWwindow* GL_WINDOW;

		//Rule of 5:
		_Window(const _Window& other) = delete;
		_Window(_Window&& other) = delete;
		_Window& operator=(_Window&& other) = delete;
		_Window& operator=(const _Window& other) = delete;

		static glm::vec3 direction;

	private:

		bool toggle = false;
		//Callbacks
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	public:
		_Window();
		~_Window();

		inline GLFWwindow* getWindow() { return GL_WINDOW; }

		void processInput(goof::Entity* player, int mode = GOOF_MODE_2D, GLFWwindow* window = nullptr);
		void processInput();
		void swap_and_pollevents();
		void set_cursor_lock(bool ch);
		bool isWindowOpen();

};



