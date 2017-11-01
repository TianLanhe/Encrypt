#include "PasswordManager.h"
#include <iostream>

using namespace std;

int main(){
	PasswordManager pwdMngr = new PasswordMnager();
	pwdMngr.generatePwd();
	cout << pwdMngr.getHint() << endl;
	cout << pwdMngr.getPwd() << endl;
	return 0;
}

