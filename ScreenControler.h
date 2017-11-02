#ifndef SCREEN_CONTROLER_H
#define SCREEN_CONTROLER_H

#include <Windows.h>
#include <algorithm>

enum Type {
	MOUSE, KEYBOARD, UNKNOWN
};

struct Point {
	Point(int x, int y) :x(x), y(y) {}
	Point() :x(0), y(0) {}
	int x;
	int y;
};

class Range {

public:
	Range(const Point& p1, const Point& p2) { setRange(p1.x, p1.y, p2.x, p2.y); }
	Range(int x1, int y1, int x2, int y2) { setRange(x1, y1, x2, y2); }
	Range() {}

	void setRange(int x1, int y1, int x2, int y2) {
		m_p1 = Point(min(x1, x2), min(y1, y2));
		m_p2 = Point(max(x1, x2), max(y1, y2));
	}

	int top() { return m_p1.y; }
	int bottom() { return m_p2.y; }
	int left() { return m_p1.x; }
	int right() { return m_p2.x; }

	int height() { return bottom() - top(); }
	int width() { return right() - left(); }

private:
	Point m_p1;
	Point m_p2;
};

class ScreenControler {
public:
	ScreenControler();

	void PutCursor();
	void HideCursor();

	void Goto(const Point& p1) { Goto(p1.x, p1.y); }
	void Goto(int x, int y);

	Type GetInput();
	Point GetMousePos();
	char GetKeyBoardCode();

	void Clear();

private:
	HANDLE m_handle;

	Point m_mouseinput;
	char m_keyboardinput;

};

#endif
