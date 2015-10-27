#include "Shader.h"
//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

Shader::Shader(const char *vertexFile, const char *fragmentFile):camera(camera) {
	programID = loadShader(vertexFile, fragmentFile);
	glUseProgram(programID);

	matrixID = glGetUniformLocation(programID, "modelMatrix");
	myLoc = glGetUniformLocation(programID, "lightPosition");
	GL_CHECK_ERRORS();
}

void Shader::setCamera(Camera& camera) {
	camera.registerObserver(this);
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

void Shader::update(glm::vec3 vector) {

}

void Shader::shaderRotate(float rotationx) {
	glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(rotationx), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &r[0][0]);
}


