#include "UIMainScreen.h"
#include "UIEncryptScreen.h"
#include "UIDecryptScreen.h"
#include <iostream>
#include <string>

using namespace std;

enum Code {
	Encrypt,Decrypt
};

void UIMainScreen::_PrintMainMenu() {
	cout << endl;
	cout << "            ����������������������ӭʹ�ü��ܽ��ܳ��򩤩�����������              " << endl;
	cout << "            ��  ����������������������������������������������  ��              " << endl;
	cout << "            ��  ��                                          ��  ��              " << endl;
	cout << "            ��  ��               author: HeZhenyu           ��  ��              " << endl;
	cout << "            ��  ��         mail: hezhenyu96@foxmail.com     ��  ��              " << endl;
	cout << "            ��  ��               github: TianLanhe          ��  ��              " << endl;
	cout << "            ��  ����������������������������������������������  ��              " << endl;
	cout << "            ��                                                  ��              " << endl;
	cout << "            ��              ��ѡ�� 1. �ļ�����                ��              " << endl;
	cout << "            ��                       2. �ļ�����                ��              " << endl;
	cout << "            ��                       3. �˳�����                ��              " << endl;
	cout << "            ��                                                  ��              " << endl;
	cout << "            ������������������������������������������������������              " << endl;
}

void UIMainScreen::Start() {
	system("cls");
	_PrintMainMenu();

	cout << "��������ȷѡ����س�ȷ����";

	int code = -1;
	while (cin >> code && code != 1 && code != 2 && code != 3)
		cout << "��������ȷ��ѡ�";

	if (code != 1 && code != 2)
		_SetReturnCode(UIControler::Stop);
	else if(code == 1)
		_SetReturnCode(Encrypt);
	else if (code == 2)
		_SetReturnCode(Decrypt);
}

UIScreen* UIMainScreen::Transform(int code) {
	switch (code)
	{
	case Encrypt:
		return new UIEncryptScreen(m_controler);
		break;
	case Decrypt:
		return new UIDecryptScreen(m_controler);
		break;
	default:
		return nullptr;
	}
}
