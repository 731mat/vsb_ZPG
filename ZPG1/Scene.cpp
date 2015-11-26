#include "Scene.h"
#include "Application.h"


Scene::Scene()
{
	compileShaders();
	objManager = new ObjectManager;
	camera = new Camera;
	light = new Light(lambert, objManager);
	light2 = new Light(20, 0, -50);
	lights.push_back(light);
	lights.push_back(light2);
	phong->updateLights(lights);
	light2->registerObserver((OnChangeLightObserver*)phong);
	light->registerObserver((OnChangeLightObserver*)phong);
	camera->registerObserver((OnChangeCameraObserver*)lambert);
	camera->registerObserver((OnChangeCameraObserver*)phong);

	objManager->setMesh("sphere", new Mesh(GL_TRIANGLES, sphereVertices, sphereCount));
	objManager->setMesh("worker", new Mesh(GL_TRIANGLES, workerVertices, workerCount));
	objManager->setMesh("box", new Mesh(GL_TRIANGLES, boxVertices, boxCount));
	objManager->setMesh("suzi", new Mesh(GL_TRIANGLES, suziVertices, suziCount));
	objManager->setMesh("jumper", new Mesh(GL_TRIANGLES, jumpVertices, jumpCount));
	objManager->setMesh("plane", new Mesh(GL_TRIANGLES, plane , 10));

	drawables.push_back(new Object(objManager->getMesh("sphere"), phong, glm::vec3(0, 2, 0), glm::vec3(1, 1, 1)));
	drawables.push_back(new Object(objManager->getMesh("worker"), phong, glm::vec3(0, -2, 0), glm::vec3(1, 1, 1)));
	drawables.push_back(new Object(objManager->getMesh("jumper"), phong, glm::vec3(-2, 0, 0), glm::vec3(1, 1, 1)));
	drawables.push_back(new Object(objManager->getMesh("suzi"), phong, glm::vec3(2, 0, 0), glm::vec3(1, 1, 1)));
	drawables.push_back(new Object(objManager->getMesh("plane"), phong, glm::vec3(0, -3, 0), glm::vec3(100, 1, 1)));
	camera->notifyObserver();
	light->notifyObserver();
}

Scene::~Scene()
{
	delete light;
	delete light2;
	delete camera;
	for (unsigned int i = 0; i < drawables.size(); i++)
		delete drawables[i];
}


void Scene::compileShaders()
{
	//light->registerObserver((OnChangeLightObserver*)shader);
	//camera->registerObserver((OnChangeCameraObserver*)shader);
	lambert = new Shader("Lambert-VS.glsl", "Lambert-FS.glsl");
	//shader = new Shader("VertexShader.glsl", "FragmentShader.glsl");
	phong = new Shader("Phong-VS.glsl", "Phong-FS.glsl");
}

void Scene::drawObj()
{
	glStencilFunc(GL_ALWAYS, 0, 0xFF);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	light->draw();
	updateLight(light);
	for (unsigned int i = 0; i < drawables.size(); i++)
	{
		glStencilFunc(GL_ALWAYS, i + 1, 0xFF);
		drawables[i]->draw();
	};
}

void Scene::addObj(double x, double y, bool plant)
{
	int width = Application::getWindow()->width, height = Application::getWindow()->height;
	GLbyte color[4];
	GLfloat depth;
	int newy = (int)Application::height - InputMouse::mouseCursor.y;
	glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
	glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
	printf("Clicked on pixel %f, %f, color % 02hhx % 02hhx % 02hhx % 02hhx, depth %f, stencil index %u\n", x, y, color[0], color[1], color[2], color[3], depth, index);
	if (plant == true)
	{
		glm::vec3 screenX = glm::vec3(x, newy, depth);
		glm::mat4& view = getCamera()->getView();
		glm::mat4& projection = getCamera()->getProjection();
		glm::vec4& viewPort = glm::vec4(0, 0, width, height);
		glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);
		drawables.push_back(new Object(objManager->getMesh("box"), phong, glm::vec3(pos.x, pos.y, pos.z), glm::vec3(1, 1, 1)));
		printf("unProject[%f, %f, %f]\n", pos.x, pos.y, pos.z);
	}
}

void Scene::delObj()
{
	int x = InputMouse::mouseCursor.x;
	int y = InputMouse::mouseCursor.y;
	int newy = (int)Application::height - InputMouse::mouseCursor.y;
	glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
	if (index != 0 && drawables.size() != 0)
	{
		drawables.erase(drawables.begin() + index - 1);
	}
}

void Scene::moveObj(glm::vec3 position)
{

//	int newy = (int)Application::height - InputMouse::mouseCursor.y;
	//glReadPixels(InputMouse::mouseCursor.x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
	if (index != 0)
		drawables[index - 1]->setPosition(position);
}

void Scene::updateLight(Light* light)
{
	phong->updateLights(lights);
}

Camera* Scene::getCamera()
{
	return camera;
}

Light* Scene::getLight()
{
	return light;
}

ObjectManager* Scene::getObjMan()
{
	return objManager;
}
