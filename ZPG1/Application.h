#ifndef application_h_
#define application_h_

#include <GL/glew.h>
#include <GLFW/glfw3.h>  

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "Shader.h"
#include "Camera.h"
#include "opengl_helper.h"

class Application{
private:
	
	static Application* objectInstance;
	GLFWwindow* window;
	Shader* shader;
	Camera* camera;
	GLuint VBO;
	GLuint VAO;
	GLchar type;
	int count;
	float rotationx;

	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow *window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);

	void createObj();
	void callbackKeys();
	void setVerGL(int major, int minor);
	void getVerGL();
	void compileShaders();
	void drawObj();
	void static moved(int key);
	
	Application(int width, int height, const char* title);

public:
	static Application* getWindow();

	~Application();

	void renderObject();
	void mainloop();

	Shader* getShader();

	static int width, height;
	static std::string title;
};
#endif application_h_