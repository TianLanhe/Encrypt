#ifndef UI_LOGIN_SCREEN_H
#define UI_LOGIN_SCREEN_H

#include "../include/UIScreen.h"

class UILoginScreen : public UIScreen {

public:
	UILoginScreen(UIControler* controler) :UIScreen(controler) {}

	void Start();
	UIScreen* Transform(int);

private:
	void _PrintLoginMenu();
	void _EnterPassword();

};

#endif
