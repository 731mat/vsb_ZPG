#include "Application.h"
#include "bedna.h"

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

	int fwidth = 800, fheight = 600;
	float ratio = fwidth / (float)fheight;
	glViewport(0, 0, fwidth, fheight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

	GL_CHECK_ERRORS();
	glGetError();
	
	controller->setController(window);
	compileShaders();
	camera = new Camera;
	camera->registerObserver((AbstractObserver*)shader);
	//glEnable(GL_DEPTH_TEST); 
}


Application::~Application() {
	glfwDestroyWindow(window);
	glfwTerminate();
}


void Application::mainloop() {
	rotationx = 0;
	renderObject();
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
	rotationx += 0.5f;
	shader->shaderRotate(rotationx);
	camera->moveUp();
	
	glBindVertexArray(VAO);
	// draw triangles
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei) pocetPrvku); //mode,first,count
	}

void Application::renderObject() {

	VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
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