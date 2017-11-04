#include "UILoginScreen.h"
#include "UIMainScreen.h"
#include "../../core/PasswordManager.h"
#include <iostream>
#include <conio.h>

using namespace std;

enum Code {
	LOGIN
};

void UILoginScreen::_PrintLoginMenu() {
	cout << endl;
	cout << "            ����������������������ӭʹ�ü��ܽ��ܳ��򩤩�����������              " << endl;
	cout << "            ��                                                  ��              " << endl;
	cout << "            ��    �������������룬�����������ʹ��.             ��              " << endl;
	cout << "            ��                                                  ��              " << endl;
	cout << "            ��              ��ѡ�� 1. ��������                ��              " << endl;
	cout << "            ��                       2. �˳�����                ��              " << endl;
	cout << "            ��                                                  ��              " << endl;
	cout << "            ������������������������������������������������������              " << endl;
}

UIScreen* UILoginScreen::Transform(int code) {
	switch (code) {
	case LOGIN:
		return new UIMainScreen(m_controler);
	default:
		return nullptr;
	}
}

void UILoginScreen::Start() {
	_PrintLoginMenu();
	cout << "��������ȷѡ����س�ȷ����";

	int code = -1;
	while (cin >> code && code != 1 && code != 2)
		cout << "��������ȷ��ѡ�";

	if (code != 1)
		_SetReturnCode(UIControler::Stop);
	else
		_EnterPassword();
}

void UILoginScreen::_EnterPassword() {
	PasswordManager pwdmgr;
	pwdmgr.generatePwd();

	cout << "������ʾ��" << pwdmgr.getHint() << endl;

	string pwd;
	for (int try_time = 3; try_time != 0; --try_time) {
		if (try_time == 3)
			cout << "����������(��0�˳�����)��";
		else
			cout << "��Ǹ���������" << endl << "�㻹�� " << try_time << " �λ��᣺";

		cin >> pwd;

		if (pwd == "0") {
			_SetReturnCode(UIControler::Stop);
			return;
		}
		else if (pwdmgr.checkPwd(pwd)) {
			cout << "������ȷ��(�����������˵�)";
			getch();
			_SetReturnCode(LOGIN);
			return;
		}
	}
	_SetReturnCode(UIControler::Stop);
}
