#ifndef UI_CONTROLER_H
#define UI_CONTROLER_H

class UIScreen;

class UIControler {

public:
	UIControler() :m_nCode(Stop), m_screen(nullptr) { }
	~UIControler();

	void Transform(int);
	void Start();
	int GetReturnCode() { return m_nCode; }
	void SetReturnCode(int code) { m_nCode = code; }

public:
	static const int Stop;

private:
	int m_nCode;
	UIScreen* m_screen;

};

#endif
