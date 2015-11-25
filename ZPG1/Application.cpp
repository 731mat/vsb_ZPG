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
	glfwSwapInterval(1);
	
	glfwSetErrorCallback(controller->error_callback);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_DEPTH_TEST); 
	glEnable(GL_STENCIL_TEST);


	int fwidth = 800, fheight = 600;
	float ratio = fwidth / (float)fheight;
	glViewport(0, 0, fwidth, fheight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

	GL_CHECK_ERRORS();
	glGetError();
	//setVerGL(4.5, 4.5);
	scene = new Scene;
	controller->setController(window);
}

Application::~Application() {

	delete scene;
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Application::mainloop() {

	while (!glfwWindowShouldClose(window))
	{
		keysClicked();
		mouseClick();
		scene->drawObj();
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}

void Application::keysClicked() {
	if (Controller::keys[87] == true)
	{
		scene->getCamera()->moveForward();
	}
	if (Controller::keys[83] == true)
	{
		scene->getCamera()->moveBack();
	}
	if (Controller::keys[65] == true)
	{
		scene->getCamera()->moveLeft();
	}
	if (Controller::keys[68] == true)
	{
		scene->getCamera()->moveRight();
	}
	if (Controller::keys[264] == true)
	{
		scene->getLight()->move(glm::vec3(0.0f, -0.5f, 0.0f));
	}
	if (Controller::keys[265] == true)
	{
		scene->getLight()->move(glm::vec3(0.0f, 0.5f, 0.0f));
	}
	if (Controller::keys[263] == true)
	{
		scene->getLight()->move(glm::vec3(-0.5f, 0.0f, 0.0f));
	}
	if (Controller::keys[262] == true)
	{
		scene->getLight()->move(glm::vec3(0.5f, 0.0f, 0.0f));
	}
	if (Controller::keys[77] == true)
	{
		scene->getLight()->move(glm::vec3(0.0f, 0.0f, 0.5f));
	}
	if (Controller::keys[78] == true)
	{
		scene->getLight()->move(glm::vec3(0.0f, 0.0f, -0.5f));
	}
	/*if (Controller::keys[87] == true)
	{
		scene->getCamera()->moveForward();
	}
	if (Controller::keys[87] == true)
	{
		scene->getCamera()->moveForward();

	}*/
	
}

void Application::mouseClick() {
	if (Controller::mouseBut[1] == true)
		scene->getCamera()->cursorCallback(Controller::mouseCur.x, Controller::mouseCur.y);
	if (Controller::mouseBut[0] == true)
		scene->addObj(Controller::mouseCur.x, Controller::mouseCur.y);


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

Scene* Application::getScene() {
	return scene;
}