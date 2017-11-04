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
	cout << "            ┌─────────欢迎使用加密解密程序──────┐              " << endl;
	cout << "            │  ┌─────────────────────┐  │              " << endl;
	cout << "            │  │                                          │  │              " << endl;
	cout << "            │  │               author: HeZhenyu           │  │              " << endl;
	cout << "            │  │         mail: hezhenyu96@foxmail.com     │  │              " << endl;
	cout << "            │  │               github: TianLanhe          │  │              " << endl;
	cout << "            │  └─────────────────────┘  │              " << endl;
	cout << "            │                                                  │              " << endl;
	cout << "            │              请选择： 1. 文件加密                │              " << endl;
	cout << "            │                       2. 文件解密                │              " << endl;
	cout << "            │                       3. 退出程序                │              " << endl;
	cout << "            │                                                  │              " << endl;
	cout << "            └─────────────────────────┘              " << endl;
}

void UIMainScreen::Start() {
	system("cls");
	_PrintMainMenu();

	cout << "请输入正确选项并按回车确定：";

	int code = -1;
	while (cin >> code && code != 1 && code != 2 && code != 3)
		cout << "请输入正确的选项：";

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
