
#include "Application.h"
#include "opengl_helper.h"

#include <stdio.h>

int main(void)
{
	Application* window = Application::getWindow();
	window->mainloop();
	exit(EXIT_SUCCESS);
}
