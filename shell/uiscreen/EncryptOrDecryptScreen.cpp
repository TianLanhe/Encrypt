#include "EncryptOrDecryptScreen.h"
#include <iostream>
#include <string>
#include <fstream>
#include "../../core/Encrypt.h"
#include "ScreenControler.h"

using namespace std;

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

	fstream test;
	test.open(outfilename, ios::in);
	while (test) {
		test.close();
		if (outfilename == filename)
			cout << m_oper << "����ļ���������ԭ�ļ�����ͬ�����������룺";
		else
			cout << outfilename << "�Ѵ��ڣ����������룺";
		getline(cin, outfilename);
		test.open(outfilename, ios::in);
	}

	string pwd;
	string pwd_check;
	do {
		cout << "������" << m_oper << "������(������15λ)��";
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
		cout << "���ٴ�����" << m_oper << "�����룺";
		getline(cin, pwd_check);
		if (pwd != pwd_check)
			cout << "������������벻һ�£����������룡" << endl;
	} while (pwd != pwd_check);

	cout << "����" << m_oper << "...";

	EncryptData data;
	in >> data;
	bool result = data.Encrypt(pwd);

	if (!result) {
		cout << endl;
		cout << "�ļ� \"" << filename << "\"" << m_oper << "ʧ��" << endl;
	}
	else {
		ofstream outfile(outfilename, ios::binary);
		if (!outfile) {
			cout << endl;
			cout << "�޷���������ļ� \"" << outfilename << "\"��" << m_oper << "ʧ�ܣ�" << endl;
		}
		else {
			outfile << data;
			cout << endl;
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
