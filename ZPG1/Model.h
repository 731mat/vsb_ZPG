#ifndef model_h_
#define model_h_
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
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "AssimpMesh.h"
#include "Drawable.h"

class Model : public Drawable
{
private:
	GLuint numFaces;
	GLuint VAO;
	GLuint VBO;
	GLuint IBO;

	int indicesCount = 0;
	int static models;
	unsigned int numMeshe;
	string name;
	aiMaterial* mat;
	Assimp::Importer importer;
	GLuint tex_2d;
	const aiScene* scene = NULL;

public:
	Model();
	Model(string name);
	~Model();
	GLint texture;
	void draw();
	void Import3DFromFile(const std::string& pFile);
};

#endif model_h_
