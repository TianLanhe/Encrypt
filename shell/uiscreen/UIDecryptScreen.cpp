#include "../../core/Encrypt.h"
#include "UIDecryptScreen.h"
#include "UIMainScreen.h"
#include <fstream>
#include <string>
#include <iostream>
#include <climits>
#include "ScreenControler.h"

#undef max	// Windows.h������max�꣬Ӱ����c++��max������ʹ��

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
	cout << "������Ҫ���ܵ��ļ�������·����";
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
	cout << "��������ܺ���ļ�������·����";
	getline(cin, outfilename);

	fstream test;
	test.open(outfilename, ios::in);
	while (test) {
		test.close();
		if (outfilename == filename)
			cout << "���ܺ���ļ���������ԭ�ļ�����ͬ�����������룺";
		else
			cout << outfilename << "�Ѵ��ڣ����������룺";
		getline(cin, outfilename);
		test.open(outfilename, ios::in);
	}

	string pwd;
	string pwd_check;
	do {
		cout << "��������ܵ�����(������15λ)��";
		getline(cin, pwd);
		/*	while ((length = strlen(password)) > 15) {
				printf("�Բ������볤��15λ�����������루����0���ز˵�����");
				fflush(stdin);
				gets(password);
				if (!(strcmp(password, "0"))) {
					fclose(fin);
					fclose(fout);
					return;
				}
			}*/
		cout << "���ٴ�������ܵ����룺";
		getline(cin, pwd_check);
		if (pwd != pwd_check)
			cout << "������������벻һ�£����������룡" << endl;
	} while (pwd != pwd_check);

	cout << "���ڽ���...";

	EncryptData data;
	in >> data;
	bool result = data.Decrypt(pwd);

	if (!result) {
		cout << endl;
		cout << "�ļ� \"" << filename << "\"����ʧ��" << endl << endl;
	}
	else {
		ofstream outfile(outfilename, ios::binary);
		if (!outfile) {
			cout << endl;
			cout << "�޷���������ļ� \"" << outfilename << "\"������ʧ�ܣ�";
		}
		else {
			outfile << data;
			cout << endl;
			cout << "�ļ� \"" << filename << "\"���ܳɹ��������� \"" << outfilename << "\" ��" << endl;
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
