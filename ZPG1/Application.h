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
#include "Controller.h"
#include "opengl_helper.h"

class Application{
private:
	
	static Application* objectInstance;
	GLFWwindow* window;
	Shader* shader;
	Camera* camera;
	Controller* controller;
	GLuint VBO;
	GLuint VAO;
	//GLchar type;
	int count;
	float rotationx;

	void createObj();

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