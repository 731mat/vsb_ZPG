#include "Scene.h"
#include "Application.h"


Scene::Scene()
{
	compileShaders();
	mshManager = new MeshManager;
	camera = new Camera;
	skybox = new Skybox(skyboxShader);
	light = new Light(LightShader, mshManager);
	light2 = new Light(20, 0, 35);
	light3 = new Light(10, 0, -20);
	lights.push_back(light);
	lights.push_back(light2);
	phong->updateLights(lights);
	light2->registerObserver((OnChangeLightObserver*)phong);
	light3->registerObserver((OnChangeLightObserver*)phong);
	light->registerObserver((OnChangeLightObserver*)phong);
	camera->registerObserver((OnChangeCameraObserver*)skyboxShader);
	camera->registerObserver((OnChangeCameraObserver*)LightShader);
	camera->registerObserver((OnChangeCameraObserver*)phong);
<<<<<<< HEAD
	camera->registerObserver(skybox);
	skybox->loadSkybox("skybox/front.jpg", "skybox/back.jpg", "skybox/left.jpg", "skybox/right.jpg", "skybox/top.jpg", "skybox/bottom.jpg"); // mountains + ocean
	//skybox->loadSkybox("skybox/ft.jpg", "skybox/bk.jpg", "skybox/lf.jpg", "skybox/rt.jpg", "skybox/up.jpg", "skybox/dn.jpg"); 
	//skybox->loadSkybox("skybox/arctic_ft.tga", "skybox/arctic_bk.tga", "skybox/arctic_lf.tga", "skybox/arctic_rt.tga", "skybox/arctic_up.tga", "skybox/arctic_dn.tga"); //Snow Terrain
	skybox->loadSkybox("skybox/arrakisday_ft.tga", "skybox/arrakisday_bk.tga", "skybox/arrakisday_lf.tga", "skybox/arrakisday_rt.tga", "skybox/arrakisday_up.tga", "skybox/arrakisday_dn.tga"); //Desert
	this->loadObjects();
=======

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
>>>>>>> origin/master
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
	skyboxShader = new Shader("Skybox-VS.glsl", "Skybox-FS.glsl");
	LightShader = new Shader("Lambert-VS.glsl", "Lambert-FS.glsl");
	phong = new Shader("Phong-VS.glsl", "Phong-FS.glsl");
}

void Scene::drawObj()
{
	glGetError();
	glStencilFunc(GL_ALWAYS, 0, 0xFF);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//skybox->drawSkybox();
	light->draw();
	updateLight(light);

	for (unsigned int i = 0; i < drawables.size(); i++)
	{
		glStencilFunc(GL_ALWAYS, i + 1, 0xFF);
		drawables[i]->draw();
	};
	GL_CHECK_ERRORS();
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
	float x = InputMouse::mouseCursor.x;
	float y = InputMouse::mouseCursor.y;
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

void Scene::rotObjX(float rotateX)
{
	if (index != 0)
		drawables[index - 1]->rotateZ(rotateX);
}
void Scene::rotObjY(float rotateY)
{
	if (index != 0)
		drawables[index - 1]->rotateY(rotateY);
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

void Scene::loadObjects()
{
	printf("\n\nLoading objects _________________________________ \n\n");
	
	//mshManager->setObj("street", new Model("models/street/Street environment_V01.obj"));
	mshManager->setObj("jumper", new Model("models/jumper/Puddle Jumper.obj"));
	//mshManager->setObj("tree", new Model("models/trees/palm_tree.obj"));
	//mshManager->setObj("house", new Model("models/house.obj"));
	//mshManager->setObj("cannon", new Model("models/Cannon.obj"));
	//mshManager->setObj("grass", new Model("models/grass/grass_01.obj"));
	//mshManager->setObj("desert-city", new Model("models/Desert_City/desert city.obj"));
	//mshManager->setObj("BattleDroid", new Model("models/BattleDroid.obj"));
	//mshManager->setObj("R2D2", new Model("models/r2-d2/R2-D2.obj"));
	//mshManager->setObj("starship", new Model("models/arc170/ARC170.obj"));
	//mshManager->setObj("han", new Model("models/Han/HanSmooth.obj"));
	//mshManager->setObj("at-st", new Model("models/at/atst.obj"));
	//mshManager->setObj("bob", new Model("models/Boba_Fett.dae"));
	//mshManager->setObj("bob", new Model("models/Boba_Fett.dae"));
	//mshManager->setObj("c-3po", new Model("models/C-3PO/C-3PO.obj"));
	//mshManager->setObj("sidious", new Model("models/sidious/Darth_Sidious.obj"));
	//mshManager->setObj("at-at", new Model("models/at-at/at-at.obj"));
	//shManager->setObj("nanosuit", new Model("models/nanosuit/nanosuit.obj"));
	//mshManager->setObj("falcon", new Model("models/falcon/Millennium_Falcon.obj"));
	//mshManager->setObj("snowPlane", new Model("models/snowTerrain/SnowTerrain1.obj"));
	//mshManager->setObj("plane", new Model("models/plane.obj"));
	//mshManager->setObj("mountains-plane", new Model("models/mountains-plane/table-mountain.obj"));
	//mshManager->setObj("lambo", new Model("models/avent/test.obj"));
	//mshManager->setObj("sevcik", new Model("models/sev0099/sevcik.obj"));
	

	printf("\n\nLoading header files ______________________ \n\n");

	mshManager->setMesh("sphere", new Mesh(GL_TRIANGLES, sphereVertices, sphereCount, "sphere"));
	//mshManager->setMesh("worker", new Mesh(GL_TRIANGLES, workerVertices, workerCount, "worker"));
	//mshManager->setMesh("box", new Mesh(GL_TRIANGLES, boxVertices, boxCount, "box"));
	//mshManager->setMesh("suzi", new Mesh(GL_TRIANGLES, suziVertices, suziCount, "suzi"));
	//mshManager->setMesh("plane", new Mesh(GL_TRIANGLES, planeVertices, planeCount, "plane"));

	drawables.push_back(new Object(mshManager->getObj("jumper"), phong, glm::vec3(-10, 4, 20), glm::vec3(0.5, 0.5, 0.5)));
	drawables.push_back(new Object(mshManager->getObj("jumper"), phong, glm::vec3(-20, 4, 30), glm::vec3(0.5, 0.5, 0.5)));
	drawables.push_back(new Object(mshManager->getObj("jumper"), phong, glm::vec3(-30, 4, 20), glm::vec3(0.5, 0.5, 0.5)));
	drawables.push_back(new Object(mshManager->getObj("jumper"), phong, glm::vec3(-40, 4, 20), glm::vec3(0.5, 0.5, 0.5)));
	drawables.push_back(new Object(mshManager->getObj("jumper"), phong, glm::vec3(-50, 4, 20), glm::vec3(0.5, 0.5, 0.5)));

		//drawables.push_back(new Object(mshManager->getMesh("suzi"), phong, glm::vec3(0, 10, 0), glm::vec3(1, 1, 1)));
		//drawables.push_back(new Object(mshManager->getMesh("sphere"), phong, glm::vec3(5, 0, 20), glm::vec3(1, 1, 1)));
	drawables.push_back(new Object(mshManager->getObj("bob"), phong, glm::vec3(-2, 5, -1), glm::vec3(1, 1, 1)));
	drawables.push_back(new Object(mshManager->getObj("at-at"), phong, glm::vec3(3, 0, 2), glm::vec3(1, 1, 1)));
	drawables.push_back(new Object(mshManager->getObj("sidious"), phong, glm::vec3(-8, 0, -2), glm::vec3(1, 1, 1)));
	drawables.push_back(new Object(mshManager->getObj("BattleDroid"), phong, glm::vec3(-6, 0, -1), glm::vec3(1, 1, 1)));
	drawables.push_back(new Object(mshManager->getObj("at-st"), phong, glm::vec3(-4, 0, -1), glm::vec3(2, 2, 2)));
	drawables.push_back(new Object(mshManager->getObj("falcon"), phong, glm::vec3(2, 20, -2000), glm::vec3(0.03, 0.03, 0.03)));
	drawables.push_back(new Object(mshManager->getObj("R2D2"), phong, glm::vec3(8, 0, -2), glm::vec3(1, 1, 1)));
	drawables.push_back(new Object(mshManager->getObj("c-3po"), phong, glm::vec3(6, 0, -1), glm::vec3(1, 1, 1)));
	drawables.push_back(new Object(mshManager->getObj("han"), phong, glm::vec3(2, 0, 0), glm::vec3(0.1, 0.1, 0.1)));
	drawables.push_back(new Object(mshManager->getObj("starship"), phong, glm::vec3(0, 500, -1000), glm::vec3(0.01, 0.01, 0.01)));

	drawables.push_back(new Object(mshManager->getObj("cannon"), phong, glm::vec3(5, 0, 10), glm::vec3(1, 1, 1)));
	drawables.push_back(new Object(mshManager->getObj("lambo"), phong, glm::vec3(0, 0, -10), glm::vec3(1, 1, 1)));
	drawables.push_back(new Object(mshManager->getObj("house"), phong, glm::vec3(10, 0, -20), glm::vec3(1, 1.5, 1)));
	drawables.push_back(new Object(mshManager->getObj("house"), phong, glm::vec3(-15, 0, 10), glm::vec3(1, 1, 0.5)));
	drawables.push_back(new Object(mshManager->getObj("house"), phong, glm::vec3(25, 0, 10), glm::vec3(0.5, 1, 0.5)));
	drawables.push_back(new Object(mshManager->getObj("sevcik"), phong, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
	drawables.push_back(new Object(mshManager->getObj("grass"), phong, glm::vec3(2, 0, -1), glm::vec3(1, 1, 1)));
	drawables.push_back(new Object(mshManager->getObj("grass"), phong, glm::vec3(3, 0, 0), glm::vec3(1, 1, 1)));
	drawables.push_back(new Object(mshManager->getObj("grass"), phong, glm::vec3(4, 0, 1), glm::vec3(1, 1, 1)));

	drawables.push_back(new Object(mshManager->getObj("street"), phong, glm::vec3(0, 0, -10), glm::vec3(1, 1, 1)));
	drawables.push_back(new Object(mshManager->getObj("mountains-plane"), phong, glm::vec3(0, -1, 0), glm::vec3(1, 1, 1)));
	drawables.push_back(new Object(mshManager->getObj("snowPlane"), phong, glm::vec3(0, -3, 0), glm::vec3(1, 1, 1)));
	drawables.push_back(new Object(mshManager->getObj("plane"), phong, glm::vec3(0, -1, 0), glm::vec3(100, 0.1, 100)));
}