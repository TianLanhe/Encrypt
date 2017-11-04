#include "ScreenControler.h"
#include <iostream>
#include <string>

using namespace std;

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

void ScreenControler::SetCursor(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(m_handle, coord);
}

Point ScreenControler::GetCursor() {
	CONSOLE_SCREEN_BUFFER_INFO    bInfo;
	GetConsoleScreenBufferInfo(m_handle, &bInfo);
	return Point(bInfo.dwCursorPosition.X, bInfo.dwCursorPosition.Y);
}

void ScreenControler::Clear(int lines) {
	CONSOLE_SCREEN_BUFFER_INFO    bInfo;
	GetConsoleScreenBufferInfo(m_handle, &bInfo);
	for (int i = 0; i < lines; ++i)
		cout << string(bInfo.dwSize.X, ' ');
}
