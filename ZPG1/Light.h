#ifndef light_h_
#define light_h_

#include "GLFW\glfw3.h"
#include <iostream>
#include <string>
#include "OnChangeLightSubject.h"
class Light : public OnChangeLightSubject {
private:
	float x, y, z;
public:
	Light();
	~Light();
	float getPosX();
	float getPosY();
	float getPosZ();
	void move(glm::vec3 moveVec);
	void setPosX(float x);
	void setPosY(float y);
	void setPosZ(float z);

	void registerObserver(OnChangeLightObserver* observer);
	void removeObserver(OnChangeLightObserver* observer);
	void notifyObserver();
};

#endif light_h_