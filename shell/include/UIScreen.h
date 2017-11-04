#ifndef UI_SCREEN_H
#define UI_SCREEN_H

#include "UIControler.h"

class UIScreen {

public:
	UIScreen(UIControler* c) :m_controler(c) {}
	virtual ~UIScreen() {}

	virtual void Start() = 0;
	virtual UIScreen* Transform(int) = 0;

protected:
	void _SetReturnCode(int code) {
		m_controler->SetReturnCode(code);
	}

	UIControler* m_controler;

};

#endif
