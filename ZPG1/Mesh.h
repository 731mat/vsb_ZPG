#ifndef mesh_h_
#define mesh_h_
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include "Shader.h"
//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "Vertex.h"
#include "models\heads\bedna.h"
#include "models\heads\sphere.h"
#include "models\heads\suzi_flat.h"
#include "models\heads\worker.h"
#include "models\heads\plane.h"
#include "Drawable.h"
class Mesh : public Drawable
{
private:
	GLuint VAO;
	GLuint VBO;
	GLenum type;
	GLsizei count;
	Vertex * vertices;
	string name;
	static int drawables;
//	std::vector<AssimpMesh*> asMesh;

public:
	Mesh(GLenum type, Vertex * vertices, float count, string name);
	Mesh();
	~Mesh();
	void draw();
	void setObject();
};
#endif mesh_h_
