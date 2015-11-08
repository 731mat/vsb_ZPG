#ifndef light_h_
#define light_h_

#include "GLFW\glfw3.h"
#include <iostream>
#include <string>
#include "OnChangeLightSubject.h"
class Light : public OnChangeLightSubject {
private:
	GLint x, y, z;
public:
	Light();
	~Light();
	GLint getPosX();
	GLint getPosY();
	GLint getPosZ();
	void setPosX(float x);
	void setPosY(float y);
	void setPosZ(float z);
	void setPos(std::string position);
	void registerObserver(OnChangeLightObserver* observer);
	void removeObserver(OnChangeLightObserver* observer);
	void notifyObserver();
};

#endif light_h_