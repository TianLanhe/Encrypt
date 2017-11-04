#include "../../core/Encrypt.h"
#include "UIDecryptScreen.h"
#include "UIMainScreen.h"
#include <fstream>
#include <string>
#include <iostream>
#include <climits>
#include "ScreenControler.h"

#undef max	// Windows.h定义了max宏，影响了c++里max函数的使用

using namespace std;

enum Code {
	MAIN, DECRYPT
};

string _GetPassword(int min, int max) {
	return "";
}

void UIDecryptScreen::Start() {
	ScreenControler sc;
	Point p = sc.GetCursor();

	string filename;
	cout << "请输入要解密的文件名及其路径：";
	cin.ignore();		//忽略之前输入时留下的换行
	getline(cin, filename);

	ifstream in;
	in.open(filename, ios::binary);
	while (!in) {
		cout << "无法打开 \"" << filename << "\" ,可能路径与文件名有误,请重新输入（输入0返回菜单）：";
		getline(cin, filename);
		if (filename == "0") {
			_SetReturnCode(MAIN);
			return;
		}
		in.open(filename, ios::binary);
	}

	string outfilename;
	cout << "请输入解密后的文件名及其路径：";
	getline(cin, outfilename);

	fstream test;
	test.open(outfilename, ios::in);
	while (test) {
		test.close();
		if (outfilename == filename)
			cout << "解密后的文件名不能与原文件名相同，请重新输入：";
		else
			cout << outfilename << "已存在，请重新输入：";
		getline(cin, outfilename);
		test.open(outfilename, ios::in);
	}

	string pwd;
	string pwd_check;
	do {
		cout << "请输入解密的密码(不长于15位)：";
		getline(cin, pwd);
		/*	while ((length = strlen(password)) > 15) {
				printf("对不起，密码长于15位，请重新输入（输入0返回菜单）：");
				fflush(stdin);
				gets(password);
				if (!(strcmp(password, "0"))) {
					fclose(fin);
					fclose(fout);
					return;
				}
			}*/
		cout << "请再次输入解密的密码：";
		getline(cin, pwd_check);
		if (pwd != pwd_check)
			cout << "两次输入的密码不一致，请重新输入！" << endl;
	} while (pwd != pwd_check);

	cout << "正在解密...";

	EncryptData data;
	in >> data;
	bool result = data.Decrypt(pwd);

	if (!result) {
		cout << endl;
		cout << "文件 \"" << filename << "\"解密失败" << endl << endl;
	}
	else {
		ofstream outfile(outfilename, ios::binary);
		if (!outfile) {
			cout << endl;
			cout << "无法创建输出文件 \"" << outfilename << "\"，解密失败！";
		}
		else {
			outfile << data;
			cout << endl;
			cout << "文件 \"" << filename << "\"解密成功，保存在 \"" << outfilename << "\" ！" << endl;
		}
	}

	in.close();
	cout << endl;
	cout << "接下来你希望：" << endl;
	cout << "1.继续当前操作." << endl;
	cout << "2.返回主菜单." << endl;
	cout << "3.退出程序." << endl;

	int code = -1;
	while (cin >> code && code != 1 && code != 2 && code != 3)
		cout << "请输入正确的选项：";

	if (code != 1 && code != 2)
		_SetReturnCode(UIControler::Stop);
	else if (code == 1) {
		_SetReturnCode(DECRYPT);
		sc.SetCursor(p);
		sc.Clear(14);
		sc.SetCursor(p);
	}
	else if (code == 2)
		_SetReturnCode(MAIN);
}

UIScreen* UIDecryptScreen::Transform(int code) {
	switch (code)
	{
	case MAIN:
		return new UIMainScreen(m_controler);
	case DECRYPT:
		return new UIDecryptScreen(m_controler);
	default:
		return nullptr;
	}
}
