#include "Light.h"

Light::Light() {
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