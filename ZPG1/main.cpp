#include "Application.h"
#include "opengl_helper.h"

#include <stdio.h>

int main(void)
{
	Application* window = Application::getWindow();
	//Camera *camera = new Camera;
	//Shader *shader = window->getShader(); // ty tady vytvaris uplne novy shader, ktery vubec neni nacteny z tech souboru, jen mu predas kameru a je prazdny , j� jsem se inspiroval tim observerem od N�mce, jen�e jsem nev�d�l jak vytov�it kameru a z�rove� p�edat i ty podprogramy
	// tak stejne jak mas na radku pod timhle, setterem
	//shader->setCamera(*camera);
	//camera->setCamera(shader->getShader());

	GL_CHECK_ERRORS();

	//camera->removeObserver(shader);
	window->mainloop();
	
	delete window;

	exit(EXIT_SUCCESS);
}
