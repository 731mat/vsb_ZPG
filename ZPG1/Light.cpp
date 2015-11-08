#include "Light.h"

#include <GLFW/glfw3.h>


//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr


Light::Light() {
	//float lightAmbient[] = new float[] { 0.2f, 0.3f, 0.6f, 1.0f };
	//float lightDiffuse[] = new float[] { 0.2f, 0.3f, 0.6f, 1.0f };
	//float lightPosition[] = new float[] {0, 0, 3, 1};

	//glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);	//Setup The Ambient Light
	//glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, 2.0);	//Setup The Diffuse Light
	//glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 2.0);	//Position The Light
	//glEnable(GL_LIGHT0);
	x = 0.f;
	y = 0.f;
	z = 0.f;
}

float Light::getPosX() {
	return x;
}
float Light::getPosY() {
	return y;
}
float Light::getPosZ() {
	return z;
}
void Light::setPosX(float x) {
	Light::x = x;
}
void Light::setPosY(float y) {
	Light::y = y;
}
void Light::setPosZ(float z) {
	Light::z = z;
}

void Light::move(glm::vec3 moveVec) {
	this->x += moveVec.x;
	this->y += moveVec.y;
	this->z += moveVec.z;
	notifyObserver();
}

void Light::registerObserver(OnChangeLightObserver* observer) {
	lightObservers.push_back(observer);
}
void Light::removeObserver(OnChangeLightObserver* observer) {
	lightObservers.remove(observer);
}
void Light::notifyObserver() {
	std::list<OnChangeLightObserver*>::iterator pos = this->lightObservers.begin();
	while (pos != this->lightObservers.end())
	{
		((OnChangeLightObserver*)(*pos))->updateLight(this);
		++pos;
	}
}