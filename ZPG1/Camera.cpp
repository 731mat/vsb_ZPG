#include "Camera.h"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <list>

Camera::Camera() {
	//position
	eye = glm::vec3(0.f, 0.f, 5);
	//direction
	center = glm::vec3(0, 0, -1.f);
	//idk exactlz
	UP = glm::vec3(0.f, 1.f, 0.f);
}

glm::mat4 Camera::getProjection(){
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	return glm::perspective(45.f, 4.0f / 3.0f, 0.1f, 100.0f);
}
glm::vec3 Camera::getLight(){
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	return glm::normalize(glm::vec3(-0.3, 11.0, -3.f));
}

 glm::mat4 Camera::getCamera(void){
	 return glm::lookAt(eye, eye + center, UP);
 }

 void Camera::setCamera(GLint programID) {

 	 viewMatrixID = glGetUniformLocation(programID, "viewMatrix");
	 projectMatrixID = glGetUniformLocation(programID, "projectionMatrix");
	 lightPositionID = glGetUniformLocation(programID, "lightPosition");

	 glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &getCamera()[0][0]);
	 glUniformMatrix4fv(projectMatrixID, 1, GL_FALSE, &getProjection()[0][0]);
	// glProgramUniform3f(programID, lightPositionID, light->getPosX(), light->getPosY(), light->getPosZ());
	 notifyObserver();
 }

 void Camera::registerObserver(AbstractObserver* observer) {
	 observers.push_back(observer);
	 printf("Registrovano");
 }
 void Camera::removeObserver(AbstractObserver* observer){
	 observers.remove(observer);
	 printf("Odstraneno");
 }
 void Camera::notifyObserver() {
	 std::list<AbstractObserver*>::iterator pos = this->observers.begin();
	 while (pos != this->observers.end())
	 {
		 ((AbstractObserver*)(*pos))->update(glm::vec3(0.f, 1.f, 0.f));
		 ++pos;
	 }

 }


 void Camera::moveForward() {
	 // 1,3,5//
	 center = glm::vec3(0, 0, -1);
	 eye += center * 0.030f;

 }

 void Camera::moveBack() {
	 eye -= center * 0.005f;
 }

 void Camera::moveRight() {
	 center = glm::vec3(0, -100, 1);
	 eye += 0.005f * glm::normalize(glm::cross(center, UP));
 }

 void Camera::moveLeft() {
	 center = glm::vec3(0, 3, 5);
	 eye -= 0.005f * glm::normalize(glm::cross(center, UP));
 }

 void Camera::moveUp() {
	 center -= 0.00030f * UP;
 }

 void Camera::moveDown() {
	 center += 0.00030f * UP;
 }