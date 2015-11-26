#ifndef inputMouse_h_
#define inputMouse_h_

class InputMouse
{
private:
public:
	InputMouse();
	~InputMouse();
	static bool mouseClick[];
	static glm::vec2 mouseCursor;
	static void buttonClicked();
};

#endif inputMouse_h_