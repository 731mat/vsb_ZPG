#include "Controller.h"
#include "Application.h"
#include <cstdio>

void Controller::setController(GLFWwindow* window) {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(window, button_callback);
	glfwSetWindowFocusCallback(window, window_focus_callback);
	glfwSetWindowIconifyCallback(window, window_iconify_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
}

void Controller::error_callback(int error, const char* description){ fputs(description, stderr); }

void Controller::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
		glfwSetWindowShouldClose(window, GL_TRUE);
	//printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
	Application::getWindow()->KeysClicked(key);
}

void Controller::window_focus_callback(GLFWwindow* window, int focused){ printf("window_focus_callback \n"); }

void Controller::window_iconify_callback(GLFWwindow* window, int iconified){ printf("window_iconify_callback \n"); }

void Controller::window_size_callback(GLFWwindow* window, int width, int height){
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Controller::cursor_callback(GLFWwindow *window, double x, double y){ 
	//printf("cursor_callback \n"); 
	Application::getWindow()->getScene()->getCamera()->cursorCallback(x, y);
	
}

void Controller::button_callback(GLFWwindow* window, int button, int action, int mode){
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}