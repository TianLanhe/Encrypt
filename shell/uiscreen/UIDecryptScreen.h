#ifndef UI_DECRYPT_SCREEN_H
#define UI_DECRYPT_SCREEN_H

#include "EncryptOrDecryptScreen.h"

class UIDecryptScreen : public EncryptOrDecryptScreen {

public:
	UIDecryptScreen(UIControler* controler) :EncryptOrDecryptScreen("Ω‚√‹", controler) {}

	UIScreen* Transform(int);

};

#endif
