#include "../include/UIControler.h"
#include "../include/UIScreenFactory.h"
#include "../include/UIScreen.h"

const int UIControler::Stop = -1;

UIControler::~UIControler()
{
	if (m_screen)
		delete m_screen;
}

void UIControler::Start() {
	if (m_screen)
		delete m_screen;

	m_screen = UIScreenFactory::GetInstance()->GetStartScreen(this);
	m_screen->Start();
}

void UIControler::Transform(int code) {
	UIScreen* screen = m_screen->Transform(code);
	if (m_screen)
		delete m_screen;
	m_screen = screen;
	m_screen->Start();
}

