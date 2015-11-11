#ifndef light_h_
#define light_h_
#include <GL/glew.h>
#include "GLFW\glfw3.h"
#include <iostream>
#include <string>
#include "OnChangeLightSubject.h"
//#include "Drawable.h"
class Drawable;
class Shader;
class Light : public OnChangeLightSubject {
private:
	float x, y, z;
	Drawable* objLig;
public:
	Light(Shader* shader);
	~Light();
	glm::vec3 getPosition();
	void draw();
	void move(glm::vec3 moveVec);
	void registerObserver(OnChangeLightObserver* observer);
	void removeObserver(OnChangeLightObserver* observer);
	void notifyObserver();
};

#endif light_h_