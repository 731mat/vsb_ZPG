#include "AssimpMesh.h"

<<<<<<< HEAD
AssimpMesh::AssimpMesh(int id, GLuint VAO, GLuint VBO, GLuint IBO, int indicesCount)
{
	this->VAO = VAO;
	this->VBO = VBO;
	this->IBO = IBO;
	this->indicesCount = indicesCount;

=======
AssimpMesh::AssimpMesh()
{
	
>>>>>>> origin/master
}

AssimpMesh::~AssimpMesh()
{
	delete this;
}

<<<<<<< HEAD

void AssimpMesh::draw()
{	
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);
}


=======
>>>>>>> origin/master
