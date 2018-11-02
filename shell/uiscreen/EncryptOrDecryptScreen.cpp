#include "EncryptOrDecryptScreen.h"
#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <vector>
#include "../../core/Encrypt.h"
#include "ScreenControler.h"

using namespace std;

string EncryptOrDecryptScreen::_GetPassword(char echo) {
	vector<char> vec;
	char ch;
	while ((ch = getch()) != '\n' && ch != '\r') {
		if (ch == '\b') {
			if (vec.size()) {
				if (echo)
					cout << "\b \b";
				vec.pop_back();
			}
		}
		else {
			vec.push_back(ch);

			if (echo)
				cout << echo;
		}
	}
	cout << endl;
	return string(vec.begin(), vec.end());
}

void EncryptOrDecryptScreen::_adjustOutputFileName(const string& instr, string& outstr) {
	if (outstr.find('.') != string::npos || instr.rfind('.') == string::npos)
		return;

	outstr.append(instr.substr(instr.rfind('.')));
}

void EncryptOrDecryptScreen::Start() {
	ScreenControler sc;
	Point p = sc.GetCursor();	//如果重复操作，用于光标回到原来的位置

	string filename;
	cout << "请输入要" << m_oper << "的文件名及其路径：";
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
	cout << "请输入" << m_oper << "后的文件名及其路径：";
	getline(cin, outfilename);
	_adjustOutputFileName(filename, outfilename);

	fstream test;
	test.open(outfilename, ios::in);
	while (test) {
		test.close();
		if (outfilename == filename)
			cout << m_oper << "后的文件名不能与原文件名相同，请重新输入：";
		else
			cout << outfilename << "已存在，请重新输入：";
		getline(cin, outfilename);
		_adjustOutputFileName(filename, outfilename);
		test.open(outfilename, ios::in);
	}

	string pwd;
	string pwd_check;
	do {
		cout << "请输入" << m_oper << "的密码(6~15位)：";
		pwd = _GetPassword('*');

		while (pwd.size() < 6 || pwd.size() > 15)
		{
			if (pwd.size() < 6)
				cout << "对不起，密码位数小于6位，请重新输入（输入0返回菜单）：";
			else
				cout << "对不起，密码位数长于15位，请重新输入（输入0返回菜单）：";

			pwd = _GetPassword('*');
			if (pwd == "0") {
				_SetReturnCode(MAIN);
				return;
			}
		}

		cout << "请再次输入" << m_oper << "的密码：";
		pwd_check = _GetPassword('*');

		if (pwd != pwd_check)
			cout << "两次输入的密码不一致，请重新输入！" << endl;
	} while (pwd != pwd_check);


	EncryptData data;
	cout << "正在读取文件..." << endl;
	in >> data;

	cout << "文件大小：";
	double size = data.size();
	const char *unit[] = { "","KB","MB","GB" };
	int count = 0;
	while(size > 1024){
		size /= 1024;
		++count;
	}
	cout << size << unit[count] << endl;

	cout << "正在" << m_oper << "..." << endl;
	bool result = data.Encrypt(pwd);

	if (!result) {
		cout << "文件 \"" << filename << "\"" << m_oper << "失败" << endl;
	}
	else {
		ofstream outfile(outfilename, ios::binary);
		if (!outfile) {
			cout << "无法创建输出文件 \"" << outfilename << "\"，" << m_oper << "失败！" << endl;
		}
		else {
			cout << "正在保存" << m_oper << "后的文件..." << endl;
			outfile << data;
			cout << "文件 \"" << filename << "\"" << m_oper << "成功，保存在 \"" << outfilename << "\" ！" << endl;
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
		_SetReturnCode(THIS_OPERATION);
		Point cur = sc.GetCursor();
		sc.SetCursor(p);
		sc.Clear(cur.y - p.y + 1);
		sc.SetCursor(p);
	}
	else if (code == 2)
		_SetReturnCode(MAIN);
}
