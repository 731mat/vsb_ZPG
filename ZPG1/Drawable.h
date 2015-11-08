#ifndef Drawable_h_
#define Drawable_h_

#include <GL/glew.h>
#include <GLFW/glfw3.h> 
//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

class Drawable {
private:
	static int drawables;
	GLuint VAO;
	GLuint VBO;
	glm::vec3 position;
public:
	Drawable(glm::vec3 setVector);
	~Drawable();
	void draw();
	void renderObject();
};

#endif Drawable_h_