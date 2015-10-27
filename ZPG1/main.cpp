#include "Application.h"
#include "opengl_helper.h"

#include <stdio.h>

int main(void)
{
	Application* window = Application::getWindow();
	//Camera *camera = new Camera;
	//Shader *shader = window->getShader(); 
	//shader->setCamera(*camera);
	//camera->setCamera(shader->getShader());

	GL_CHECK_ERRORS();

	//camera->removeObserver(shader);
	window->mainloop();
	
	delete window;

	exit(EXIT_SUCCESS);
}
