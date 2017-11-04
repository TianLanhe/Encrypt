#ifndef UI_ENCRYPT_SCREEN_H
#define UI_ENCRYPT_SCREEN_H

#include "../include/UIScreen.h"

class UIEncryptScreen : public UIScreen {

public:
	UIEncryptScreen(UIControler* controler) :UIScreen(controler) {}

	void Start();
	UIScreen* Transform(int);

};

#endif
