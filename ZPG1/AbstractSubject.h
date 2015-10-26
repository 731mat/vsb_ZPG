#include <glm/mat4x4.hpp> // glm::mat4
#include "AbstractObserver.h"
class AbstractSubject {

public: 
	virtual void registerObserver(AbstractObserver* observer) = 0;
	virtual void removeObserver(AbstractObserver* observer) = 0;
	virtual void notifyObserver() = 0;
};