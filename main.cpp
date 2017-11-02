#include "ScreenControler.h"
#include <iostream>
using namespace std;

int main() {
	ScreenControler control;
	Type type;
	while (1) {
		type = control.GetInput();
		switch (type)
		{
		case KEYBOARD:
			cout << "KEYBOARD" << endl;
			break;
		case MOUSE:
			cout << "MOUSE" << endl;
			break;
		default:
			cout << "UNKNOWN" << endl;
			break;
		}
	}
	while (1);
	return 0;
}

