#pragma once
#include <glm/mat4x4.hpp> // glm::mat4
class Light;
class OnChangeLightObserver{

public:
	virtual ~OnChangeLightObserver()
	{
	}

	virtual void updateLight(Light* light) = 0;
};