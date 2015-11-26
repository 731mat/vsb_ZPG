#ifndef camera_h_
#define camera_h_
#include <GL/glew.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "OnChangeCameraSubject.h"
#include "Light.h"
#include "stdio.h"

class Application;
class Camera : public OnChangeCameraSubject {

private:
	float curX, curY,xPos,yPos,zPos;
	glm::vec3 eye;
	glm::vec3 center;
	glm::vec3 UP;

public:
	Camera();
	~Camera();
	glm::mat4 getView();
	glm::mat4 getProjection();
	void lookAt(glm::vec3 center, glm::vec3 up);
	void moveForward();
	void moveBack();
	void moveRight();
	void moveLeft();
	void moveDown();
	void moveUp();

	glm::vec3 getEye();

	void cursorCallback(float x, float y);
	void registerObserver(OnChangeCameraObserver* observer);
	void removeObserver(OnChangeCameraObserver* observer);
	void notifyObserver();

};
#endif camera_h_