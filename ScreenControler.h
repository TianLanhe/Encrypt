#ifndef SCREEN_CONTROLER_H
#define SCREEN_CONTROLER_H

#include <algorithm>

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
		m_p1 = Point(std::min(x1, x2), std::min(y1, y2));
		m_p2 = Point(std::max(x1, x2), std::max(y1, y2));
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
	void PutCursor();
	void HideCursor();

	void Goto(const Point& p1) { Goto(p1.x, p1.y); }
	void Goto(int x, int y);

	void Clear();

};

#endif
