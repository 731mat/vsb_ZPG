#ifndef objectManager_h_
#define objectManager_h_
#include <map>
#include "Object.h"
#include "Mesh.h"

class ObjectManager
{
private:
	std::map< std::string, Mesh> models;
public:
	Mesh* getMesh(std::string name);
	void setMesh(std::string name, Mesh* mesh);
	ObjectManager();
	~ObjectManager();
};
#endif objectManager_h_
