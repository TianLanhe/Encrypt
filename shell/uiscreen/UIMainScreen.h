#ifndef UI_MAIN_SCREEN_H
#define UI_MAIN_SCREEN_H

#include "../include/UIScreen.h"

class UIMainScreen : public UIScreen {

public:
	UIMainScreen(UIControler* controler) :UIScreen(controler) {}

	void Start();
	UIScreen* Transform(int);

private:
	void _PrintMainMenu();

};

#endif
