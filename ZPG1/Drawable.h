#ifndef Drawable_h_
#define Drawable_h_

#include <GL/glew.h>
#include <GLFW/glfw3.h> 

class Drawable {
private:
	static int drawables;
	GLuint VAO;
	GLuint VBO;
public:
	Drawable();
	~Drawable();
	void draw();
	void renderObject();
};

#endif Drawable_h_