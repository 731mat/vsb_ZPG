#include <glm/mat4x4.hpp> // glm::mat4
#include "AbstractObserver.h"
#include <list>
#include <iostream>
class AbstractSubject {

public: 
	virtual void registerObserver(AbstractObserver* observer) = 0;
	virtual void removeObserver(AbstractObserver* observer) = 0;
	virtual void notifyObserver() = 0;

protected:
	std::list<AbstractObserver*> observers;
};