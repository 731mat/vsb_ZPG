#include "Skybox.h"
#include <SOIL.h>
#include <glm/detail/type_vec3.hpp>
#include <vector>
#include "Application.h"

GLfloat skyboxVertices[] = {
	-1.0f, 1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f
};

Skybox::Skybox(Shader* shader)
{
	this->shader = shader;
}

Skybox::~Skybox()
{

}

void Skybox::loadSkybox(string a_sFront, std::string a_sBack, std::string a_sLeft, std::string a_sRight, std::string a_sTop, std::string a_sBottom)
{
	tex_cube = SOIL_load_OGL_cubemap
		(
		a_sFront.c_str(), a_sBack.c_str(),
		a_sTop.c_str(), a_sBottom.c_str(),
		a_sRight.c_str(), a_sLeft.c_str(),
		SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_MULTIPLY_ALPHA
		);

		glGenVertexArrays(1, &skyboxVAO);
		glGenBuffers(1, &skyboxVBO);
		glBindVertexArray(skyboxVAO);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), static_cast<GLvoid*>(0));
		glBindVertexArray(0);

		
}

void Skybox::drawSkybox()
{
	glDepthMask(GL_FALSE);
	this->shader->setShader();
	//viewMat = glm::mat4(glm::mat3(Application::getWindow()->getScene()->getCamera()->getView()));
	//glUniformMatrix4fv(glGetUniformLocation(shader->getShader(), "view"), 1, GL_FALSE, glm::value_ptr(viewMat));
	//glUniformMatrix4fv(glGetUniformLocation(shader->getShader(), "projection"), 1, GL_FALSE, glm::value_ptr(Application::getWindow()->getScene()->getCamera()->getProjection()));
	//this->shader->setViewMatrix(Application::getWindow()->getScene()->getCamera()->getView());
	//this->shader->setProjectionMatrix(Application::getWindow()->getScene()->getCamera()->getProjection());
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex_cube);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, tex_cube);
	//glUniform1i(glGetUniformLocation(shader->getShader(), "textura"), 0);
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(shader->getShader(), "textura"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex_cube);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthMask(GL_TRUE);
}

void Skybox::updateCamera(Camera* camera)
{
	projectionMat = camera->getProjection();
	viewMat = glm::mat4(glm::mat3(camera->getView()));
	//this->shader->setShader();
	//viewMat = (camera->getView());
	//projectionMat = (camera->getProjection());
	//this->shader->setViewMatrix(camera->getView());
	//this->shader->setProjectionMatrix(camera->getProjection());
	this->drawSkybox();
}
