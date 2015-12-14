#ifndef Texture_h_
#define Texture_h_

#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <SOIL.h>
#include <cstdio>
#include <string>
//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr


class Shader;

class Texture {
private:
	std::string path;

public:
	GLuint tex_2d;
	Texture();
	~Texture();
	GLuint loadTexture();
};

#endif Texture_h_