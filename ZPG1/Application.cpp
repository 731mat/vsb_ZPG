#include "Application.h"

Application* Application::objectInstance = NULL;
int Application::width = 800;
int Application::height = 600;
std::string Application::title = "ZPG";

Application* Application::getWindow() {
	if (Application::objectInstance == NULL)
		return Application::objectInstance = new Application(Application::width, Application::height, Application::title.c_str());
	return Application::objectInstance;
}

Application::Application(int width, int height, const char* title) {
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	
	//glfwSetErrorCallback(error_callback);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_DEPTH_TEST); 

	int fwidth = 800, fheight = 600;
	float ratio = fwidth / (float)fheight;
	glViewport(0, 0, fwidth, fheight);
	glMatrixMode(GL_PROJECTION);
	////glLoadIdentity();
	////glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

	GL_CHECK_ERRORS();
	glGetError();
	setVerGL(4.5, 4.5);
	controller->setController(window);
	compileShaders();
	camera = new Camera;
	camera->registerObserver((AbstractObserver*)shader);
}


Application::~Application() {
	glfwDestroyWindow(window);
	glfwTerminate();
}


void Application::mainloop() {
	rotationx = 0;
	drawables.push_back(new Drawable());

	while (!glfwWindowShouldClose(window))
	{
		drawObj();
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}

void Application::compileShaders() {
	shader = new Shader("VertexShader.glsl", "FragmentShader.glsl");
}

void Application::drawObj() {
	glClear(GL_COLOR_BUFFER_BIT);
	shader->setShader();
	camera->setCamera(shader->getShader());
	rotationx += 1.9f;
	shader->shaderRotate(rotationx);
	camera->moveDown();
	for (int i = 0; i < drawables.size(); i++)
		drawables[i]->draw();

	}



void Application::moved(int key) {
	switch (key)
	{
	case GLFW_KEY_S:
		printf("u click");
		break;
	case GLFW_KEY_W:
		printf("u click");
		break;
	}
}

void Application::setVerGL(int major, int minor) {

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Application::getVerGL() {
	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);
}