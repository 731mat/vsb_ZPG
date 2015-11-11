#include "Light.h"
#include "Application.h"
#include <GLFW/glfw3.h>


//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr



Light::Light(Shader* shader) {
	//GLfloat spot_direction[] = { 1.0, 1.0, 0.0 }; //smìr
	//(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	//glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0f);//  (const GLfloat*)45.0f); //velikost kužele
	//float lightAmbient[] = new float[] { 0.2f, 0.3f, 0.6f, 1.0f };
	//float lightDiffuse[] = new float[] { 0.2f, 0.3f, 0.6f, 1.0f };
	//float lightPosition[] = new float[] {0, 0, 3, 1};
	x = 0.f;
	y = 0.f;
	z = 0.f;
	objLig = new Drawable(shader, getPosition(), glm::vec3(0.5, 0.5, 0.5));
}

Light::~Light() {
}

glm::vec3 Light::getPosition() {
	return glm::vec3(x, y, z);
}

void Light::draw() {
	objLig->draw();
	
}
void Light::move(glm::vec3 moveVec) {
	this->x += moveVec.x;
	this->y += moveVec.y;
	this->z += moveVec.z;
	objLig->setPosition(moveVec);
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