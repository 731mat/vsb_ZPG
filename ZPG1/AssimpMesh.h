#ifndef assimpMesh_h_
#define assimpMesh_h_
<<<<<<< HEAD
=======
#include <map>
>>>>>>> origin/master
#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include "Shader.h"
//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
<<<<<<< HEAD
=======

>>>>>>> origin/master
class AssimpMesh
{
private:
	GLuint VAO;
	GLuint VBO;
<<<<<<< HEAD
	GLuint IBO;
	int id;
	int indicesCount;
=======
>>>>>>> origin/master

public:
	static struct Verte
	{
		float Position[3];
		float Normal[3];
		float Texture[2];
		float Tangent[3];
<<<<<<< HEAD
		float Bitangens[3];
	};
	AssimpMesh(int id, GLuint VAO, GLuint VBO, GLuint IBO, int indicesCount);
	~AssimpMesh();
	void draw();
=======
	};
	AssimpMesh();
	~AssimpMesh();

>>>>>>> origin/master
};
#endif assimpMsh_h_
