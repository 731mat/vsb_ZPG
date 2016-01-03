#pragma once
#include <glm/mat4x4.hpp> // glm::mat4
#include "OnChangeCameraObserver.h"
#include <list>
#include <iostream>
class OnChangeCameraSubject {

public:
	virtual ~OnChangeCameraSubject()
	{
	}

	virtual void registerObserver(OnChangeCameraObserver* observer) = 0;
	virtual void removeObserver(OnChangeCameraObserver* observer) = 0;
	virtual void notifyObserver() = 0;

protected:
	std::list<OnChangeCameraObserver*> camsObservers;
	
};