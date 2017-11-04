#include "../core/Encrypt.h"
#include "../core/PasswordManager.h"
#include "include/UIControler.h"

int main() {
	UIControler ui;

	ui.Start();
	while (ui.GetReturnCode() != UIControler::Stop)
		ui.Transform(ui.GetReturnCode());

	return 0;
/*
	int i, *hint;                       //ѭ������i��������ʾhint[4]
	int X = 0, Y = 0;					   //��¼�����������
	char *password;					   //��ȷ����password
	int type;
	PrintLogin();                      //��ӡ��¼����
	printf("��������ȷѡ����س�ȷ��(�������ֱ�ӵ��ѡ��):");
	while (1) {
		type = GetXy(&X, &Y, 40, 47, 5, 6);
		if (type == 1) {
			if (Y == 5) {
				GotoXy(0, 9);
				for (i = 0; i < 79; i++)printf(" ");
				GotoXy(0, 9);
				hint = setHint();
				password = setPassword(hint);
				printf("������ʾ��");
				for (i = 0; i < 4; i++)printf("%c", hint[i]);
				printf("\n");
				if (isPassword(password)) {
					Y = 0;
					X = 0;
					printf("������ȷ��(�����������˵�)\n");
					HideCursor();
					free(hint);
					free(password);
					hint = NULL;
					password = NULL;
					getch();
					break;
				}
				else return 0;
			}
			else if (Y == 6) {
				GotoXy(28, 12);
				HideCursor();
				return 0;
			}
		}
		else {
			char temp;
			if (type == '1' || type == '2') {
				printf("%c", type);
				do {
					temp = getch();
				} while (temp != 13);
				printf("\n");
			}
			if (type == '2') {
				GotoXy(28, 12);
				HideCursor();
				return 0;
			}
			else if (type == '1') {
				hint = setHint();
				password = setPassword(hint);
				printf("������ʾ��");
				for (i = 0; i < 4; i++)printf("%c", hint[i]);
				printf("\n");
				if (isPassword(password)) {
					Y = 0;
					X = 0;
					printf("������ȷ��(�����������˵�)\n");
					HideCursor();
					getch();
					break;
				}
				else {
					GotoXy(28, 12);
					HideCursor();
					free(hint);
					free(password);
					return 0;
				}
			}
		}
	}
	GetXy(&X, &Y, 40, 47, 10, 12);
	while (1) {
		/*ע�����ﲻ������������system("cls")�����޷���ȡ����¼�����Ҳ��֪��Ϊʲô������δ�����Ұ�*/
/*		GotoXy(0, 0);
		PrintMenu();        			   //��ӡ�˵�
		for (i = 0; i < 640; i++)printf(" ");
		GotoXy(0, 15);
		PutCursor();
		printf("��������ȷѡ����س�ȷ��(�������ֱ�ӵ��ѡ��):");
		type = GetXy(&X, &Y, 40, 47, 10, 12);
		if (type == 1) {
			GotoXy(0, 15);
			for (i = 0; i < 79; i++)printf(" ");
			GotoXy(0, 15);
			switch (Y) {
			case 10:Encrypt(ENCRYPT); break;
			case 11:Encrypt(DECRYPT); break;
			case 12:GotoXy(28, 16);
				HideCursor();
				return 0;
			}
			X = 0;
			Y = 0;
		}
		else {
			if (type == '1' || type == '2' || type == '3')printf("%c", type);
			getch();
			switch (type) {
			case '1':Encrypt(ENCRYPT); break;
			case '2':Encrypt(DECRYPT); break;
			case '3':return 0;
			}
		}
	}
	return 0;*/
}
