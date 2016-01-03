#pragma once
#include <glm/mat4x4.hpp> // glm::mat4
class Camera;
class OnChangeCameraObserver{

public:
	virtual ~OnChangeCameraObserver()
	{
	}

	virtual void updateCamera(Camera* camera) = 0;
};