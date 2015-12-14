#ifndef inputKeyboard_h_
#define inputKeyboard_h_

class InputKeyboard
{
private:
	static void timeLoop(int time);
public:
	InputKeyboard();
	~InputKeyboard();
	 static bool keys[];
	 static void keysClicked();
};

#endif inputKeyboard_h_