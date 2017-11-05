#include "UIDecryptScreen.h"
#include "UIMainScreen.h"

using namespace std;

UIScreen* UIDecryptScreen::Transform(int code) {
	switch (code)
	{
	case MAIN:
		return new UIMainScreen(m_controler);
	case THIS_OPERATION:
		return new UIDecryptScreen(m_controler);
	default:
		return nullptr;
	}
}
