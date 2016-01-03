#include "Camera.h"

#include <glm/vec3.hpp> // glm::vec3

#include <glm/vec4.hpp> // glm::vec4

#include <glm/mat4x4.hpp> // glm::mat4

#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include "Application.h"
#include "glm/gtx/rotate_vector.hpp"
#include <list>

Camera::Camera()
{
	xPos = 0.f;
	yPos = 0.f;
	zPos = 7.f;
	//position
	eye = glm::vec3(xPos, yPos, zPos);
	//direction
	center = glm::vec3(0, 0.0f, -1.f);
	//idk exactly
	UP = glm::vec3(0.f, 1.f, 0.f);
	curX = 0;
	curY = 0;
}

Camera::~Camera()
{
}

glm::vec3 Camera::getEye()
{
	return eye;
}

glm::mat4 Camera::getProjection()
{
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	return glm::perspective(45.f, (float)Application::width / (float)Application::height, 0.1f, 100.0f);
}

glm::mat4 Camera::getView(void)
{
	return glm::lookAt(eye, eye + center, UP);
}


void Camera::registerObserver(OnChangeCameraObserver* observer)
{
	camsObservers.push_back(observer);
	printf("Registrovano\n");
}

void Camera::removeObserver(OnChangeCameraObserver* observer)
{
	camsObservers.remove(observer);
	printf("Odstraneno");
}

void Camera::notifyObserver()
{
	list<OnChangeCameraObserver*>::iterator pos = this->camsObservers.begin();
	while (pos != this->camsObservers.end())
	{
		(*pos)->updateCamera(this);
		++pos;
	}
}

void Camera::lookAt(glm::vec3 center, glm::vec3 UP)
{
	this->center = center;
	this->UP = UP;
}

void Camera::moveForward(float x)
{
	eye += center * x;
	notifyObserver();
}

void Camera::moveBack(float x)
{
	eye -= center * x;
	notifyObserver();
}

void Camera::moveRight(float x)
{
	eye += x * glm::normalize(glm::cross(center, UP));
	notifyObserver();
}

void Camera::moveLeft(float x)
{
	eye -= x * glm::normalize(glm::cross(center, UP));
	notifyObserver();
}

void Camera::moveUp(float x)
{
	center -= x * UP;
	notifyObserver();
}

void Camera::moveDown(float x)
{
	center += x * UP;
	notifyObserver();
}

void Camera::cursorCallback(float x, float y)
{

	if (curX == 0)
		curX = x;
	if (curY == 0)
		curY = y;
	float dx = -(x - curX) / 100.0f;
	float dy = -(y - curY) / 100.0f;

	center = rotateY(center, dx);
	center = rotateX(center, dy);

	//center = glm::rotateX(glm::normalize(this->center), dy);
	// UP = rotateY(UP, dx);
	lookAt(center, UP);
	// printf("%f, %f\n", dx, dy);
	curX = x;
	curY = y;
	notifyObserver();
}
