#include "Object.h"
#include "Application.h"


Object::Object(Mesh* mesh, Shader* shader, glm::vec3 setPosition, glm::vec3 setScale)
{
	this->shader = shader;
	this->mesh = mesh;
	model = glm::mat4(1.0f);
	model = glm::scale(model, setScale);
	model = glm::translate(model, setPosition);
}

Object::~Object()
{
	delete this;
}

void Object::draw()
{
	this->shader->setModelMatrix(model);
	this->mesh->draw();
}

void Object::setPosition(glm::vec3 position)
{
	this->model = glm::translate(model, position);
}
