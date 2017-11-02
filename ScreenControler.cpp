#include "ScreenControler.h"

ScreenControler::ScreenControler() {
	m_handle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void ScreenControler::PutCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1,1 };
	SetConsoleCursorInfo(m_handle, &cursor_info);
}

void ScreenControler::HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(m_handle, &cursor_info);
}

void ScreenControler::Goto(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(m_handle, coord);
}

Type ScreenControler::GetInput() {
	HANDLE hInput;                              //获取标准输入设备句柄
	INPUT_RECORD inRec;                         //返回数据记录
	DWORD res;                                  //返回已读取的记录数
	int x = -1, y = -1;
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	ReadConsoleInput(hInput, &inRec,1, &res);
	if (inRec.EventType == MOUSE_EVENT && inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
		x = (int)inRec.Event.MouseEvent.dwMousePosition.X;
		y = (int)inRec.Event.MouseEvent.dwMousePosition.Y;
		m_mouseinput = Point(x, y);
		m_keyboardinput = '\0';
		return KEYBOARD;
	}
	else if (inRec.EventType == KEY_EVENT && inRec.Event.KeyEvent.bKeyDown) {
		m_keyboardinput = inRec.Event.KeyEvent.uChar.AsciiChar;
		m_mouseinput = Point();
		return MOUSE;
	}
	return UNKNOWN;
}
