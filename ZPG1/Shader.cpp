#include "Shader.h"
#include "Application.h"
//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

Shader::Shader(const char *vertexFile, const char *fragmentFile) {
	programID = loadShader(vertexFile, fragmentFile);
	glUseProgram(programID);
	matrixID = glGetUniformLocation(programID, "modelMatrix");
	viewMatrixID = glGetUniformLocation(programID, "viewMatrix");
	projectMatrixID = glGetUniformLocation(programID, "projectionMatrix");
	lightPositionID = glGetUniformLocation(programID, "lightArray");
	viewPositionID = glGetUniformLocation(programID, "viewPosition");
	glm::mat4 r = glm::mat4();
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &r[0][0]);
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &r[0][0]);
	glUniformMatrix4fv(projectMatrixID, 1, GL_FALSE, &r[0][0]);


}


void Shader::setShader() {
    glUseProgram(programID);
}

void Shader::setTexture(GLint tex)
{
	this->setShader();
	glActiveTexture(GL_TEXTURE0);
	//glUniform1i(this->getShader(), tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	//glUniform1i(this->getShader(), 0);
	glUniform1i(glGetUniformLocation(this->getShader(), "textura"), 0);
}

Shader::~Shader() {
	this->deleteShader();
}

GLint Shader::getShader() {
	return programID;
}

void Shader::updateCamera(Camera* camera) {
	this->setShader();
	glm::vec3 cam = camera->getEye();
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &camera->getView()[0][0]);
	glUniformMatrix4fv(projectMatrixID, 1, GL_FALSE, &camera->getProjection()[0][0]);
	glUniform3f(viewPositionID,cam.x, cam.y, cam.z);

}

void Shader::updateLight(Light* light) {
	setShader();
	glm::vec3 lig = light->getPosition();
	glUniform3f(lightPositionID, lig.x, lig.y, lig.z);
}
void Shader::updateLights(std::vector<Light*> lights){
	glm::vec3 position[5];
	for (unsigned int i = 0; i < lights.size(); i++) {
		position[i] = lights[i]->getPosition();
	}
	glUniform3fv(lightPositionID, lights.size(), &position[0][0]);
	glGetError();
}

void Shader::setModelMatrix(glm::mat4 matrix) {
	setShader();
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setViewMatrix(glm::mat4 matrix) {
	setShader();
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &matrix[0][0]);

}
void Shader::setProjectionMatrix(glm::mat4 matrix) {
	setShader();
	glUniformMatrix4fv(projectMatrixID, 1, GL_FALSE, &matrix[0][0]);
}