#pragma once
#include <string>
#include <GL/glew.h>
#include <vector>
#include "Shader.h"
#include "OnChangeCameraObserver.h"


class Skybox : public OnChangeCameraObserver
{
private:
	GLint VAO;
	std::string sDirectory;
	std::string sFront, sBack, sLeft, sRight, sTop, sBottom;
	GLuint tex_cube;
	Shader* shader;
	GLuint skyboxVAO, skyboxVBO;
	glm::mat4 viewMat, projectionMat;
public:
	Skybox(Shader* shader);
	~Skybox();
	void loadSkybox(std::string a_sFront, std::string a_sBack, std::string a_sLeft, std::string a_sRight, std::string a_sTop, std::string a_sBottom);
	void drawSkybox();
	void drawSkybox() const;
	void updateCamera(Camera* camera);
};
