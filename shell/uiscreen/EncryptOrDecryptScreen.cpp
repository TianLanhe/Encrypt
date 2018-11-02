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
	Point p = sc.GetCursor();	//����ظ����������ڹ��ص�ԭ����λ��

	string filename;
	cout << "������Ҫ" << m_oper << "���ļ�������·����";
	cin.ignore();		//����֮ǰ����ʱ���µĻ���
	getline(cin, filename);

	ifstream in;
	in.open(filename, ios::binary);
	while (!in) {
		cout << "�޷��� \"" << filename << "\" ,����·�����ļ�������,���������루����0���ز˵�����";
		getline(cin, filename);
		if (filename == "0") {
			_SetReturnCode(MAIN);
			return;
		}
		in.open(filename, ios::binary);
	}

	string outfilename;
	cout << "������" << m_oper << "����ļ�������·����";
	getline(cin, outfilename);
	_adjustOutputFileName(filename, outfilename);

	fstream test;
	test.open(outfilename, ios::in);
	while (test) {
		test.close();
		if (outfilename == filename)
			cout << m_oper << "����ļ���������ԭ�ļ�����ͬ�����������룺";
		else
			cout << outfilename << "�Ѵ��ڣ����������룺";
		getline(cin, outfilename);
		_adjustOutputFileName(filename, outfilename);
		test.open(outfilename, ios::in);
	}

	string pwd;
	string pwd_check;
	do {
		cout << "������" << m_oper << "������(6~15λ)��";
		pwd = _GetPassword('*');

		while (pwd.size() < 6 || pwd.size() > 15)
		{
			if (pwd.size() < 6)
				cout << "�Բ�������λ��С��6λ�����������루����0���ز˵�����";
			else
				cout << "�Բ�������λ������15λ�����������루����0���ز˵�����";

			pwd = _GetPassword('*');
			if (pwd == "0") {
				_SetReturnCode(MAIN);
				return;
			}
		}

		cout << "���ٴ�����" << m_oper << "�����룺";
		pwd_check = _GetPassword('*');

		if (pwd != pwd_check)
			cout << "������������벻һ�£����������룡" << endl;
	} while (pwd != pwd_check);


	EncryptData data;
	cout << "���ڶ�ȡ�ļ�..." << endl;
	in >> data;

	cout << "�ļ���С��";
	double size = data.size();
	const char *unit[] = { "","KB","MB","GB" };
	int count = 0;
	while(size > 1024){
		size /= 1024;
		++count;
	}
	cout << size << unit[count] << endl;

	cout << "����" << m_oper << "..." << endl;
	bool result = data.Encrypt(pwd);

	if (!result) {
		cout << "�ļ� \"" << filename << "\"" << m_oper << "ʧ��" << endl;
	}
	else {
		ofstream outfile(outfilename, ios::binary);
		if (!outfile) {
			cout << "�޷���������ļ� \"" << outfilename << "\"��" << m_oper << "ʧ�ܣ�" << endl;
		}
		else {
			cout << "���ڱ���" << m_oper << "����ļ�..." << endl;
			outfile << data;
			cout << "�ļ� \"" << filename << "\"" << m_oper << "�ɹ��������� \"" << outfilename << "\" ��" << endl;
		}
	}

	in.close();
	cout << endl;
	cout << "��������ϣ����" << endl;
	cout << "1.������ǰ����." << endl;
	cout << "2.�������˵�." << endl;
	cout << "3.�˳�����." << endl;

	int code = -1;
	while (cin >> code && code != 1 && code != 2 && code != 3)
		cout << "��������ȷ��ѡ�";

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
