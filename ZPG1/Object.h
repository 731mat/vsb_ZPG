#ifndef Object_h_
#define Object_h_

#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include "Shader.h"
#include "Mesh.h"
#include "Model.h"
#include "Texture.h"
//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
class Shader;
class Mesh;
class Model;
class Object {
private:
	glm::mat4 model;
	Shader* shader;
	Mesh* mesh;
	Model* objModel;
	Texture* texture;
	GLint text;
	
public:
	void setPosition(glm::vec3 position);
	void rotateX(float rotateX);
	void rotateY(float rotateY);
	void rotateZ(float rotateZ);
	Object(Mesh* mesh, Shader* shader, glm::vec3 setPosition, glm::vec3 setScale);
	Object::Object(Model* objModel, Shader* shader, glm::vec3 setPosition, glm::vec3 setScale);
	~Object();
	void draw();
};

#endif Object_h_