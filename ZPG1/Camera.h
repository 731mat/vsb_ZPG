#ifndef camera_h_
#define camera_h_
#include <GL/glew.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "AbstractSubject.h"
#include "stdio.h"

class Camera : public AbstractSubject {

private:
	glm::vec3 eye;
	glm::vec3 center;
	glm::vec3 UP;
	glm::vec3 target;
	GLint viewMatrixID;
	GLint projectMatrixID;
	GLint myLoc;


public:
	Camera();
	~Camera();
	glm::mat4 getCamera();
	glm::mat4 getProjection();
	void setCamera(GLint programID);

	void moveForward();
	void moveBack();
	void moveRight();
	void moveLeft();
	void moveDown();
	void moveUp();

	void registerObserver(AbstractObserver* observer);
	void removeObserver(AbstractObserver* observer);

protected:
	void notifyObserver();

};
#endif camera_h_