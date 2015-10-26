#include <glm/mat4x4.hpp> // glm::mat4

class AbstractObserver {

public: 
	//virtual void onProjectionChanged(glm::mat4 ProjectionMaxtrix) = 0;
	//virtual void onViewChanged(glm::mat4 ViewMatrix) = 0;
	virtual void update(glm::vec3 vector) = 0;
};