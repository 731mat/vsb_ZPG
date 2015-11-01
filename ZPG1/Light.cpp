#include "Light.h"

Light::Light() {
	x = -0.3f;
	y = 11.1f;
	z = -3.f;
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