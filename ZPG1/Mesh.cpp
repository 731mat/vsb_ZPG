#include "Mesh.h"



int Mesh::drawables = 0;
Mesh::Mesh(GLenum type, Vertex * vertices, float count)
{
	VAO = drawables;
	VBO = drawables;
	drawables++;
	this->type = type;
	this->vertices = vertices;
	this->count = count;
	setObject();
}

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
	delete this;
}

void Mesh::draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)count); //mode,first,count
	glBindVertexArray(VAO);
}

void Mesh::setObject()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) *count, vertices, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)0);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), static_cast<GLvoid*>(nullptr));
	//(GLvoid*)sizeof(vertices[0].Position) - přeskočí pole velikosti 3
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), reinterpret_cast<GLvoid*>(sizeof(vertices[0].Position)));
	glBindVertexArray(0);

}
