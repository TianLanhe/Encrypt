#include "UIEncryptScreen.h"
#include "UIMainScreen.h"

enum Code {
	MAIN, ENCRYPT
};

void UIEncryptScreen::Start() {
	_SetReturnCode(UIControler::Stop);
}

UIScreen* UIEncryptScreen::Transform(int code) {
	switch (code)
	{
	case MAIN:
		return new UIMainScreen(m_controler);
	case ENCRYPT:
		return new UIEncryptScreen(m_controler);
	default:
		return nullptr;
	}
}

