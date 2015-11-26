#ifndef Controller_h_
#define Controller_h_
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.h"
#include <glm/glm.hpp>
#include "InputKeyboard.h"
#include "InputMouse.h"

class Controller {
protected:
	static bool moveMouse;
public:
	InputKeyboard* keyboard;
	InputMouse* mouse;
	
	Controller();
	~Controller();
	void setController(GLFWwindow* window);

	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow *window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);

};

#endif Controller_h_