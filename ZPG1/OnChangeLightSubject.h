#include <glm/mat4x4.hpp> // glm::mat4
#include "OnChangeLightObserver.h"
#include <list>
#include <iostream>
class OnChangeLightSubject {

public:
	virtual void registerObserver(OnChangeLightObserver* observer) = 0;
	virtual void removeObserver(OnChangeLightObserver* observer) = 0;
	virtual void notifyObserver() = 0;

protected:
	std::list<OnChangeLightObserver*> lightObservers;

};