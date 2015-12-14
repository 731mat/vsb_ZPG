#include "Object.h"
#include "Application.h"

Object::Object(Mesh* mesh, Shader* shader, glm::vec3 setPosition, glm::vec3 setScale)
{
	this->texture = new Texture;
	this->shader = shader;
	this->mesh = mesh;
	model = glm::mat4(1.0f);
	model = glm::scale(model, setScale);
	model = glm::translate(model, setPosition);
	//text = texture->loadTexture();
}

Object::Object(Model* objModel, Shader* shader, glm::vec3 setPosition, glm::vec3 setScale)
{
	this->shader = shader;
	this->objModel = objModel;
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
	

	if (mesh != NULL)
	{
//		this->shader->setTexture(this->objModel->texture);

		//this->shader->setTexture(this->texture->loadTexture());
		this->mesh->draw();
	}
	if (objModel != NULL)
	{
		
		this->shader->setTexture(this->objModel->texture);

		this->objModel->draw();
	}
}

void Object::setPosition(glm::vec3 position)
{
	this->model = glm::translate(model, position);
}

void Object::rotate(float rotateX)
{
	this->model = glm::rotate(model, glm::radians(rotateX), glm::vec3(0.0f, 1.0f, 0.0f));
}