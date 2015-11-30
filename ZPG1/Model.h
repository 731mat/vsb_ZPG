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
#include "Drawable.h"

class Model : public Drawable
{
private:
	GLuint numFaces;
	GLuint VAO;
	GLuint VBO;
	int static models;
	unsigned int numMeshe;
	string name;
	void get_bounding_box(aiVector3D* min, aiVector3D* max);
	void get_bounding_box_for_node(const aiNode* nd, aiVector3D* min, aiVector3D* max);
	void genVAOsAndUniformBuffer(const aiScene *sc);
	float scaleFactor;
	#define aisgl_min(x,y) (x<y?x:y)
	#define aisgl_max(x,y) (y>x?y:x)
	Assimp::Importer importer;
	const aiScene* scene = NULL;

public:
	Model();
	Model(string name);
	~Model();
	void draw();
	bool Import3DFromFile(const std::string& pFile);

};

#endif model_h_
