
#include "Application.h"
#include "opengl_helper.h"

#include <stdio.h>

int main(void)
{
	Application* window = Application::getWindow();
	
	//Shader *shader = window->getShader(); 
	//camera->setCamera(shader->getShader());

	GL_CHECK_ERRORS();

	//camera->removeObserver(shader);
	window->mainloop();
	
	delete window;

	exit(EXIT_SUCCESS);
}
