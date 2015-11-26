
#include "Controller.h"
#include "Application.h"
#include "InputKeyboard.h"
bool InputKeyboard::keys[1024] = {};


InputKeyboard::InputKeyboard()
{
}

InputKeyboard::~InputKeyboard()
{
}

void InputKeyboard::keysClicked() {
	if (keys[87] == true)
	{
		Application::getWindow()->getScene()->getCamera()->moveForward();
	}
	if (keys[83] == true)
	{
		Application::getWindow()->getScene()->getCamera()->moveBack();
	}
	if (keys[65] == true)
	{
		Application::getWindow()->getScene()->getCamera()->moveLeft();
	}
	if (keys[68] == true)
		Application::getWindow()->getScene()->getCamera()->moveRight();
	if (keys[264] == true)
	{
		Application::getWindow()->getScene()->getLight()->move(glm::vec3(0.0f, -0.5f, 0.0f));
	}
	if (keys[265] == true)
	{
		Application::getWindow()->getScene()->getLight()->move(glm::vec3(0.0f, 0.5f, 0.0f));
	}
	if (keys[263] == true)
	{
		Application::getWindow()->getScene()->getLight()->move(glm::vec3(-0.5f, 0.0f, 0.0f));
	}
	if (keys[262] == true)
	{
		Application::getWindow()->getScene()->getLight()->move(glm::vec3(0.5f, 0.0f, 0.0f));
	}
	if (keys[77] == true)
	{
		Application::getWindow()->getScene()->getLight()->move(glm::vec3(0.0f, 0.0f, 0.5f));
	}
	if (keys[78] == true)
	{
		Application::getWindow()->getScene()->getLight()->move(glm::vec3(0.0f, 0.0f, -0.5f));
	}
	if (keys[80] == true)
	{
		Application::getWindow()->getScene()->addObj(InputMouse::mouseCursor.x, InputMouse::mouseCursor.y, true);
	}
	if (keys[79] == true)
	{
		Application::getWindow()->getScene()->delObj();
	}
	/*if (keys[73] == true)
	{
		Application::getWindow()->getScene()->moveObj();
	}*/
	if (keys[71] == true)
	{
		Application::getWindow()->getScene()->moveObj(glm::vec3(0.0f, -0.5f, 0.0f));
	}
	if (keys[84] == true)
	{
		Application::getWindow()->getScene()->moveObj(glm::vec3(0.0f, 0.5f, 0.0f));
	}
	if (keys[70] == true)
	{
		Application::getWindow()->getScene()->moveObj(glm::vec3(-0.5f, 0.0f, 0.0f));
	}
	if (keys[72] == true)
	{
		Application::getWindow()->getScene()->moveObj(glm::vec3(0.5f, 0.0f, 0.0f));
	}
	if (keys[82] == true)
	{
		Application::getWindow()->getScene()->moveObj(glm::vec3(0.0f, 0.0f, -0.5f));
	}
	if (keys[89] == true)
	{
		Application::getWindow()->getScene()->moveObj(glm::vec3(0.0f, 0.0f, 0.5f));
	}

}
