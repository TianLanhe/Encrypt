#ifndef SCREEN_CONTROLER_H
#define SCREEN_CONTROLER_H

#include <Windows.h>

struct Point {
	Point(int x, int y) :x(x), y(y) {}
	Point() :x(0), y(0) {}
	int x;
	int y;
};

class ScreenControler {
public:
	ScreenControler();

	void PutCursor();
	void HideCursor();

	void SetCursor(const Point& p1) { SetCursor(p1.x, p1.y); }
	void SetCursor(int x, int y);

	Point GetCursor();

	void Clear(int);

private:
	HANDLE m_handle;

};

#endif
