#ifndef UI_DECRYPT_SCREEN_H
#define UI_DECRYPT_SCREEN_H

#include "../include/UIScreen.h"
#include <string>

class UIDecryptScreen : public UIScreen {

public:
	UIDecryptScreen(UIControler* controler) :UIScreen(controler) {}

	void Start();
	UIScreen* Transform(int);

private:
	std::string _GetPassword(int min, int max);
};

#endif
