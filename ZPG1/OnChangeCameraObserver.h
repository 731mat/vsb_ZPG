#include <glm/mat4x4.hpp> // glm::mat4
class Camera;
class OnChangeCameraObserver{

public: 
	//virtual void onProjectionChanged(glm::mat4 ProjectionMaxtrix) = 0;
	//virtual void onViewChanged(glm::mat4 ViewMatrix) = 0;
	virtual void updateCamera(Camera* camera) = 0;
};