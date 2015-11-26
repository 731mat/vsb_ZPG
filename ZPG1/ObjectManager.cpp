#include "ObjectManager.h"

Mesh* ObjectManager::getMesh(std::string name)
{
	return &models[name];
}

void ObjectManager::setMesh(std::string name, Mesh* mesh)
{
	models[name] = *mesh;
}

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
	delete this;
}
