#ifndef UI_ENCRYPT_SCREEN_H
#define UI_ENCRYPT_SCREEN_H

#include "EncryptOrDecryptScreen.h"

class UIEncryptScreen : public EncryptOrDecryptScreen {

public:
	UIEncryptScreen(UIControler* controler) :EncryptOrDecryptScreen("º”√‹", controler) {}

	UIScreen* Transform(int);

};

#endif
