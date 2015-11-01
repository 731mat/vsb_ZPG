#ifndef light_h_
#define light_h_

#include "GLFW\glfw3.h"
class Light {
private:
	GLint x, y, z;
public:
	Light();
	~Light();
	float getPosX();
	float getPosY();
	float getPosZ();
	void setPosX(float x);
	void setPosY(float y);
	void setPosZ(float z);
};

#endif light_h_