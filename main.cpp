#include "PasswordManager.h"
#include <iostream>

using namespace std;

int main(){
	PasswordManager pwdMngr;
	pwdMngr.generatePwd();
	cout << pwdMngr.getHint() << endl;
	cout << pwdMngr.getPwd() << endl;
	return 0;
}

