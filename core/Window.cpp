#include "Window.h"


//static member variable initialization
glm::vec3 _Window::direction = glm::vec3(0.0f);


//method implementattions;
void _Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void _Window::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{


	static double lastX = W_WIDTH /2, lastY = W_HEIGHT/2;
	static double yaw, pitch;

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;
	
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction = glm::normalize(direction);

}


void _Window::processInput()
{
	if (glfwGetKey(GL_WINDOW, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(GL_WINDOW, true);
	
}

void _Window::swap_and_pollevents()
{
	glfwPollEvents();
	glfwSwapBuffers(GL_WINDOW);

}


_Window::_Window() : GL_WINDOW(nullptr){

	direction = glm::vec3(0.0f);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GL_WINDOW = glfwCreateWindow(W_WIDTH, W_HEIGHT, "_Window", NULL, NULL);
	if (GL_WINDOW == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	
	glfwMakeContextCurrent(GL_WINDOW);

	//Initializing glad 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	glfwSetFramebufferSizeCallback(GL_WINDOW, framebuffer_size_callback);
	glfwSetCursorPosCallback(GL_WINDOW, mouse_callback);

}


_Window::~_Window()
{
	glfwTerminate();
	std::cout << "[GLFW :] Terminated" << std::endl;
}

bool _Window::isWindowOpen()
{
	return !glfwWindowShouldClose(GL_WINDOW);
}

void _Window::set_cursor_lock(bool ch)
{
	if(ch)
	glfwSetInputMode(GL_WINDOW, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
	glfwSetInputMode(GL_WINDOW, GLFW_CURSOR,GLFW_CURSOR_NORMAL);
}

void  _Window::processInput(goof::Entity * player,int mode ,GLFWwindow* window )
{
	if(window == nullptr)
	window = GL_WINDOW;
	
	if (glfwGetKey(GL_WINDOW, GLFW_KEY_F1) == GLFW_PRESS)
	{
		if (toggle == false) {
			gf_render::setWireframeMode(!toggle);
			toggle = true;
		}
		else {
			gf_render::setWireframeMode(!toggle);
			toggle = false;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (mode == GOOF_MODE_3D) {
		player->follow_camera.cameraFront = direction;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		player->up = 1;
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		player->up = -1;
	 else
		 player->up = 0;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		player->right = -1;
	 else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		player->right = 1;
	 else
		 player->right = 0;	

	 //Notice the repetation of the -1 and 1 and 0
	 //we can make a input class with it having the bindAxis functionality

}

