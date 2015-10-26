#include "Camera.h"
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr


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

 glm::mat4 Camera::getCamera(void){
	 return glm::lookAt(eye, eye + center, UP);
 }

 void Camera::setCamera(GLint programID) {

 	 viewMatrixID = glGetUniformLocation(programID, "viewMatrix");
	 projectMatrixID = glGetUniformLocation(programID, "projectionMatrix");
	 myLoc = glGetUniformLocation(programID, "lightPosition");

	 glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &getCamera()[0][0]);
	 glUniformMatrix4fv(projectMatrixID, 1, GL_FALSE, &getProjection()[0][0]);
	 /*target = glm::vec3(0, 1, -1);
	 UP -= 0.0030f * glm::normalize(glm::cross(target, eye));;
	 center -= 0.0030f * glm::normalize(glm::cross( eye+target,center));;
	 eye -= 0.0030f * glm::normalize(glm::cross(target, center));;
	 notifyObserver();*/
 }

 void Camera::registerObserver(AbstractObserver* observer) {
	 printf("Registrovano");
 }
 void Camera::removeObserver(AbstractObserver* observer){
	 printf("Odstraneno");
 }
 void Camera::notifyObserver() {
	 printf("Uz o tom viem");
 }


 void Camera::moveForward() {
	 // 1,3,5//
	 center = glm::vec3(0, 0, -1);
	 eye += center * 0.030f;
	 //position -= moveSpeed * glm::normalize(glm::cross(target, UP));
 }

 void Camera::moveBack() {
	 eye -= center * 0.005f;
 }

 void Camera::moveRight() {
	 target = glm::vec3(0, -100, 1);
	 eye += 0.005f * glm::normalize(glm::cross(target, UP));
 }

 void Camera::moveLeft() {
	 target = glm::vec3(0, 3, 5);
	 eye -= 0.005f * glm::normalize(glm::cross(target, UP));
 }

 void Camera::moveUp() {
	 center += 0.00030f * UP;
 }

 void Camera::moveDown() {
	 center += 0.00030f * UP;
 }