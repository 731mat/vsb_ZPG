#include "Scene.h"



Scene::Scene() {
	compileShaders();
	camera = new Camera;
	light = new Light(lambert);
	light->registerObserver((OnChangeLightObserver*)lambert);
	camera->registerObserver((OnChangeCameraObserver*)lambert);
	light->registerObserver((OnChangeLightObserver*)phong);
	camera->registerObserver((OnChangeCameraObserver*)phong);

	drawables.push_back(new Drawable(phong, glm::vec3(0, 2, 0), glm::vec3(1, 1, 1)));
	drawables.push_back(new Drawable(phong, glm::vec3(0, -2, 0), glm::vec3(1, 1, 1)));
	drawables.push_back(new Drawable(phong, glm::vec3(-2, 0, 0), glm::vec3(1, 1, 1)));
	drawables.push_back(new Drawable(phong, glm::vec3(2, 0, 0), glm::vec3(1, 1, 1)));

	camera->notifyObserver();
	light->notifyObserver();
	
}

Scene::~Scene() {

	delete light;
	delete camera;
	for (unsigned int i = 0; i < drawables.size(); i++)
		delete drawables[i];
}


void Scene::compileShaders() {
	//light->registerObserver((OnChangeLightObserver*)shader);
	//camera->registerObserver((OnChangeCameraObserver*)shader);
	lambert = new Shader("Lambert-VS.glsl", "Lambert-FS.glsl");
	//shader = new Shader("VertexShader.glsl", "FragmentShader.glsl");
	phong = new Shader("Phong-VS.glsl", "Phong-FS.glsl");

}

void Scene::drawObj() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	light->draw();
	for (unsigned int i = 0; i < drawables.size(); i++)
		drawables[i]->draw();
}

void Scene::updateLight(Light* light) {
	phong->updateLights(lights);
}
Camera* Scene::getCamera() {
	return camera;
}

Light* Scene::getLight() {
	return light;
}