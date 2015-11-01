#include "Drawable.h"
#include "models\suzi_smooth.h"


int Drawable::drawables = 0;
Drawable::Drawable() {
	VAO = drawables;
	VBO = drawables;
	renderObject();
}
void Drawable::draw() {
	
	glBindVertexArray(VAO);
	// draw triangles
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)pocetPrvku); //mode,first,count
	glBindVertexArray(0);
}

void Drawable::renderObject() {
	///VertexDrawable::VertexDrawable(const Vertex* vertices, float verticesCount, MyShader  *shader)
	////VAO = 0;
	//glGenVertexArrays(1, &VAO);
	//glBindVertexArray(VAO);

	////VBO = 0;
	//glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	//glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), static_cast<GLvoid*>(nullptr));
	//(GLvoid*)sizeof(vertices[0].Position) - pøeskoèí pole velikosti 3
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), reinterpret_cast<GLvoid*>(sizeof(vertices[0].Position)));
	glBindVertexArray(0);

}
