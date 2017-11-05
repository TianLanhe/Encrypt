#include "UIEncryptScreen.h"
#include "UIMainScreen.h"

using namespace std;

UIScreen* UIEncryptScreen::Transform(int code) {
	switch (code)
	{
	case MAIN:
		return new UIMainScreen(m_controler);
	case THIS_OPERATION:
		return new UIEncryptScreen(m_controler);
	default:
		return nullptr;
	}
}

