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
<<<<<<< HEAD
	
=======
>>>>>>> origin/master
	//text = texture->loadTexture();
}

Object::Object(Model* objModel, Shader* shader, glm::vec3 setPosition, glm::vec3 setScale): mesh(nullptr), texture(nullptr), text(0)
{
	this->shader = shader;
	this->objModel = objModel;
	model = glm::mat4(1.0f);
	model = glm::scale(model, setScale);
	model = glm::translate(model, setPosition);
	
}

Object::~Object()
{
}

void Object::draw()
{
	
	this->shader->setModelMatrix(model); 
<<<<<<< HEAD
	this->shader->setShader();

	if (mesh != NULL)
	{
		//this->shader->setTexture(this->objModel->texture);
=======
	

	if (mesh != NULL)
	{
//		this->shader->setTexture(this->objModel->texture);

>>>>>>> origin/master
		//this->shader->setTexture(this->texture->loadTexture());
		this->mesh->draw();
	}
	if (objModel != NULL)
	{
<<<<<<< HEAD
		if (this->objModel->textureNormal != -1)
			this->shader->setTexture(this->objModel->texture, this->objModel->textureNormal, true);
		else
			this->shader->setTexture(this->objModel->texture, this->objModel->textureNormal, false);
=======
		
		this->shader->setTexture(this->objModel->texture);

>>>>>>> origin/master
		this->objModel->draw();
	}
}

void Object::setPosition(glm::vec3 position)
{
	this->model = glm::translate(model, position);
}

void Object::rotateX(float rotateX)
{
	this->model = glm::rotate(model, glm::radians(rotateX), glm::vec3(1.0f, 0.0f, 0.0f));
}

void Object::rotateY(float rotateY)
{
	this->model = glm::rotate(model, glm::radians(rotateY), glm::vec3(0.0f, 1.0f, 0.0f));
}
void Object::rotateZ(float rotateZ)
{
	this->model = glm::rotate(model, glm::radians(rotateZ), glm::vec3(0.0f, 0.0f, 1.0f));
}