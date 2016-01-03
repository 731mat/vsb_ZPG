#include "AssimpMesh.h"

AssimpMesh::AssimpMesh(int id, GLuint VAO, GLuint VBO, GLuint IBO, int indicesCount)
{
	this->VAO = VAO;
	this->VBO = VBO;
	this->IBO = IBO;
	this->indicesCount = indicesCount;

}

AssimpMesh::~AssimpMesh()
{
	delete this;
}


void AssimpMesh::draw()
{	
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);
}


