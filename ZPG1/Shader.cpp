#include "Shader.h"
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
	lightPositionID = glGetUniformLocation(programID, "lightPosition");
	viewPositionID = glGetUniformLocation(programID, "viewPosition");
	glm::mat4 r = glm::mat4();
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &r[0][0]);
}


void Shader::setShader() {
    glUseProgram(programID);
}

Shader::~Shader() {
	this->deleteShader();
}

GLint Shader::getShader() {
	return programID;
}

void Shader::updateCamera(Camera* camera) {
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &camera->getCamera()[0][0]);
	glUniformMatrix4fv(projectMatrixID, 1, GL_FALSE, &camera->getProjection()[0][0]);
	glUniform3f(viewPositionID,camera->getPosX(),camera->getPosY(), camera->getPosZ() );
	//glm::vec3 vec = neco.getVector();
	//glUniform3f(lokace, vec.x, vec.y, vec.z);
}

void Shader::updateLight(Light* light) {
	glUniform3f(lightPositionID, light->getPosX(), light->getPosY(), light->getPosZ());
	
}
void Shader::setModelMatrix(glm::vec3 setVector) {
	glm::mat4 r = glm::translate(glm::mat4(1.0f), setVector);
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &r[0][0]);
}
void Shader::shaderRotate(float rotationx) {
	glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(rotationx), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &r[0][0]);
}


