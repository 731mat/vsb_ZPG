#include "Application.h"
#include "Camera.h"
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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	
	glfwSetErrorCallback(error_callback);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	int fwidth = 800, fheight = 600;
	glViewport(0, 0, fwidth, fheight);
	//glEnable(GL_DEPTH_TEST);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

	glGetError();

	GL_CHECK_ERRORS();
	
	compileShaders();
	callbackKeys();
}


Application::~Application() {
	glfwDestroyWindow(window);
	glfwTerminate();

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


// Sets the key callback
void Application::callbackKeys() {
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(window, key_callback);
/*	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(window, button_callback);
	glfwSetWindowFocusCallback(window, window_focus_callback);
	glfwSetWindowIconifyCallback(window, window_iconify_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);//  */
}

void Application::mainloop() { // render už ti teda funguje, sorry, že jsem ti pár vìcí rozrýpal, ale musel jsem lokalizovat tu chybu.
	// doporucuju si v tom udelat trochu vetsi poradek a pouzivat git, aby se ti prave tohle nestavalo :-D uz jdu spat, tak to kdyztak dame dokupy dneska pozdeji. dobrou noc :-)
	rotationx = 0;
	renderObject();

	glm::mat4 model;
	GLint loc = glGetUniformLocation(this->shader->getID(), "modelMatrix");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));

	loc = glGetUniformLocation(this->shader->getID(), "viewMatrix");
	glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 5.0f), glm::vec3(0.0, 0.0, 2.0f) + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view));

	loc = glGetUniformLocation(this->shader->getID(), "projectionMatrix");
	glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projection));

	GL_CHECK_ERRORS();

	// šla ti ta bedna zobrazit pøedtím? ano ale jak jsem tam dal observer tak už nic 
	// asi to nemáš verzované co? nìkde bych to mìl mít bez observeru
	while (!glfwWindowShouldClose(window))
	{
		//glUseProgram(this->shader->getID()); tvoje grafárna si ze mì dìlá srandu..jak to ? z nìjakého dùvodu když se 2x zapíše do výstupní barvy ve fragment shaderu, tak to pøestane vykreslovat :-D a to je problém  ? :D
		// no tak je to problém, když kvùli tomu strávím pùl hodiny hledáním chyby :-D
		drawObj();
		glfwPollEvents();
		glfwSwapBuffers(window);

		GL_CHECK_ERRORS();
	}
}

void Application::compileShaders() {
	shader = new Shader("VertexShader.glsl", "FragmentShader.glsl");
}

void Application::drawObj() {
	glClear(GL_COLOR_BUFFER_BIT);
	shader->setShader();
	//camera->setCamera(shader->getShader());
	//rotationx += 0.5f;
	//shader->shaderRotate(rotationx);
//	camera->moveDown();
	
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

	/*/ vertex buffer object(VBO)
	VBO = 0;
	Object::type = type;
	Object::count = count;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, byteSize, points, GL_STATIC_DRAW);
	//vertex attribute object(VAO)
	VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	
	//// vertex buffer object(VBO)
	//VBO1 = 0;
	//glGenBuffers(1, &VBO1); // generate the VBO
	//glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	//glBufferData(GL_ARRAY_BUFFER, byteSize, points2, GL_STATIC_DRAW);
	////vertex attribute object(VAO)
	//VAO1 = 0;
	//glGenVertexArrays(1, &VAO1);
	//glBindVertexArray(VAO1);
	//glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	*/
	

}

Shader* Application::getShader()
{
	return this->shader;
};

void Application::moved(int key) {
	switch (key)
	{
	case GLFW_KEY_S:
		
		//camera->moveForward();
		//camera->moveForward();

		printf("u click");
		break;
	case GLFW_KEY_W:
		
		//camera->moveBack();
		printf("u click");
		break;
	}
}

void Application::error_callback(int error, const char* description){ fputs(description, stderr); }

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
	moved(key);
}

void Application::window_focus_callback(GLFWwindow* window, int focused){ printf("window_focus_callback \n"); }

void Application::window_iconify_callback(GLFWwindow* window, int iconified){ printf("window_iconify_callback \n"); }

void Application::window_size_callback(GLFWwindow* window, int width, int height){
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Application::cursor_callback(GLFWwindow *window, double x, double y){ printf("cursor_callback \n"); }

void Application::button_callback(GLFWwindow* window, int button, int action, int mode){
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}
