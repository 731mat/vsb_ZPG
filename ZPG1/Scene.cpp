#include "Scene.h"
#include "Application.h"


Scene::Scene()
{
	compileShaders();
	mshManager = new MeshManager;
	camera = new Camera;
	light = new Light(LightShader, mshManager);
	light2 = new Light(20, 0, 35);
	light3 = new Light(10, 0, -20);
	lights.push_back(light);
	lights.push_back(light2);
	phong->updateLights(lights);
	light2->registerObserver((OnChangeLightObserver*)phong);
	light3->registerObserver((OnChangeLightObserver*)phong);
	light->registerObserver((OnChangeLightObserver*)phong);
	camera->registerObserver((OnChangeCameraObserver*)LightShader);
	camera->registerObserver((OnChangeCameraObserver*)phong);

	mshManager->setObj("jumper", new Model("models/Puddle Jumper.obj"));
	mshManager->setObj("tree", new Model("models/trees/tree.obj"));
	mshManager->setObj("house", new Model("models/house.obj"));
	mshManager->setObj("cannon", new Model("models/Cannon.obj"));
	mshManager->setObj("plane", new Model("models/plane.obj"));
	mshManager->setObj("grass", new Model("models/grass/grass_01.obj"));
	mshManager->setObj("R2D2", new Model("models/R2-D2.obj"));
	mshManager->setObj("BattleDroid", new Model("models/BattleDroid.obj"));
	mshManager->setObj("starship", new Model("models/ARC170.obj"));
	mshManager->setObj("skydom", new Model("models/Skydome.obj"));

	mshManager->setMesh("sphere", new Mesh(GL_TRIANGLES, sphereVertices, sphereCount, "sphere"));
	mshManager->setMesh("worker", new Mesh(GL_TRIANGLES, workerVertices, workerCount, "worker"));
	mshManager->setMesh("box", new Mesh(GL_TRIANGLES, boxVertices, boxCount, "box"));
	mshManager->setMesh("suzi", new Mesh(GL_TRIANGLES, suziVertices, suziCount, "suzi"));
	//mshManager->setMesh("plane", new Mesh(GL_TRIANGLES, planeVertices, planeCount, "plane"));

	drawables.push_back(new Object(mshManager->getObj("jumper"), phong, glm::vec3(-10, 4, 20), glm::vec3(0.5,0.5, 0.5)));
	drawables.push_back(new Object(mshManager->getObj("jumper"), phong, glm::vec3(-20, 4, 30), glm::vec3(0.5,0.5, 0.5)));
	drawables.push_back(new Object(mshManager->getObj("jumper"), phong, glm::vec3(-30, 4, 20), glm::vec3(0.5,0.5, 0.5)));
	drawables.push_back(new Object(mshManager->getObj("jumper"), phong, glm::vec3(-40, 4, 20), glm::vec3(0.5,0.5, 0.5)));
	drawables.push_back(new Object(mshManager->getObj("jumper"), phong, glm::vec3(-50, 4, 20), glm::vec3(0.5,0.5, 0.5)));

	drawables.push_back(new Object(mshManager->getMesh("suzi"), phong, glm::vec3(0, 10, 0), glm::vec3(1, 1, 1)));
	drawables.push_back(new Object(mshManager->getMesh("sphere"), phong, glm::vec3(5, 0, 20), glm::vec3(1, 1, 1)));

	drawables.push_back(new Object(mshManager->getObj("cannon"), phong, glm::vec3(5, 0, 10), glm::vec3(1, 1, 1)));
	drawables.push_back(new Object(mshManager->getObj("house"), phong, glm::vec3(10, 0, -20), glm::vec3(1, 1.5, 1)));
	drawables.push_back(new Object(mshManager->getObj("house"), phong, glm::vec3(-15, 0, 10), glm::vec3(1, 1, 0.5)));
	drawables.push_back(new Object(mshManager->getObj("house"), phong, glm::vec3(25, 0, 10), glm::vec3(0.5, 1, 0.5)));
	drawables.push_back(new Object(mshManager->getObj("R2D2"), phong, glm::vec3(-4, 0, 0), glm::vec3(1, 1, 1)));
	drawables.push_back(new Object(mshManager->getObj("BattleDroid"), phong, glm::vec3(2, 0, 0), glm::vec3(1, 1, 1)));
	drawables.push_back(new Object(mshManager->getObj("starship"), phong, glm::vec3(0, 500, -2000), glm::vec3(0.01, 0.01, 0.01)));
	drawables.push_back(new Object(mshManager->getObj("plane"), phong, glm::vec3(0, -1, 0), glm::vec3(100, 0.1, 100)));
	drawables.push_back(new Object(mshManager->getObj("skydom"), phong, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
	drawables.push_back(new Object(mshManager->getObj("grass"), phong, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
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
	delete this;
}


void Scene::compileShaders()
{
	//light->registerObserver((OnChangeLightObserver*)shader);
	//camera->registerObserver((OnChangeCameraObserver*)shader);
	//shader = new Shader("VertexShader.glsl", "FragmentShader.glsl");
	LightShader = new Shader("Lambert-VS.glsl", "Lambert-FS.glsl");
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
		drawables.push_back(new Object(mshManager->getObj("tree"), phong, glm::vec3(pos.x, pos.y, pos.z), glm::vec3(1, 1, 1)));
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
	if (index != 0)
		drawables[index - 1]->setPosition(position);
}

void Scene::rotObj(float rotateX)
{
	if (index != 0)
		drawables[index - 1]->rotate(rotateX);
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

MeshManager* Scene::getObjMan()
{
	return mshManager;
}
