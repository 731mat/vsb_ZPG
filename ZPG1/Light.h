#ifndef light_h_
#define light_h_
#include <GL/glew.h>
#include "GLFW\glfw3.h"
#include <iostream>
#include <string>
#include "OnChangeLightSubject.h"
#include "ObjectManager.h"
//#include "Object.h"
class Object;
class Shader;
class ObjectManager;
class Light : public OnChangeLightSubject {
private:
	float x, y, z;
	Object* objLig;
public:
	Light(Shader* shader, ObjectManager* objManager);
	Light(float x, float y, float z);
	~Light();
	glm::vec3 getPosition();
	glm::vec3 getPositionDirection();
	void draw();
	void move(glm::vec3 moveVec);
	void registerObserver(OnChangeLightObserver* observer);
	void removeObserver(OnChangeLightObserver* observer);
	void notifyObserver();
};

#endif light_h_