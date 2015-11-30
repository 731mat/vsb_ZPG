#include "MeshManager.h"

Mesh* MeshManager::getMesh(std::string name)
{
	return &models[name];
}

Model* MeshManager::getObj(std::string name)
{
	return &objModels[name];
}

void MeshManager::setObj(std::string name, Model* model)
{
	objModels[name] = *model;
}

void MeshManager::setMesh(std::string name, Mesh* mesh)
{
	models[name] = *mesh;
}

MeshManager::MeshManager()
{
}

MeshManager::~MeshManager()
{
	delete this;
}
