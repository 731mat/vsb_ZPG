#ifndef scene_h_
#define scene_h_

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
#include "Object.h"
#include "Light.h"
#include "opengl_helper.h"
#include "MeshManager.h"
#include "Texture.h"


class Scene : public OnChangeLightObserver{
private:

	Shader *LightShader, *phong;
	Camera* camera;
	Light* light, *light2;
	MeshManager* mshManager;
	Texture* texture;
	GLuint index;
	std::vector<Object*> drawables;

	void createObj();
	void compileShaders();

public:

	std::vector<Light*> lights;
	Scene();
	~Scene();
	void drawObj();
	void addObj(double x, double y, bool plant = false);
	void delObj();
	void moveObj(glm::vec3 position);
	void rotObj(float rotateX);
	void updateLight(Light* light);
	Camera* getCamera();
	Light* getLight();
	MeshManager* getObjMan();
};
#endif scene_h_