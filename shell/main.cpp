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
	int i, *hint;                       //循环变量i，密码提示hint[4]
	int X = 0, Y = 0;					   //记录鼠标点击的坐标
	char *password;					   //正确密码password
	int type;
	PrintLogin();                      //打印登录界面
	printf("请输入正确选项并按回车确定(或用鼠标直接点击选项):");
	while (1) {
		type = GetXy(&X, &Y, 40, 47, 5, 6);
		if (type == 1) {
			if (Y == 5) {
				GotoXy(0, 9);
				for (i = 0; i < 79; i++)printf(" ");
				GotoXy(0, 9);
				hint = setHint();
				password = setPassword(hint);
				printf("密码提示：");
				for (i = 0; i < 4; i++)printf("%c", hint[i]);
				printf("\n");
				if (isPassword(password)) {
					Y = 0;
					X = 0;
					printf("密码正确！(按任意键进入菜单)\n");
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
				printf("密码提示：");
				for (i = 0; i < 4; i++)printf("%c", hint[i]);
				printf("\n");
				if (isPassword(password)) {
					Y = 0;
					X = 0;
					printf("密码正确！(按任意键进入菜单)\n");
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
		/*注意这里不能用清屏函数system("cls")，会无法读取鼠标事件，我也不知道为什么，交给未来的我吧*/
/*		GotoXy(0, 0);
		PrintMenu();        			   //打印菜单
		for (i = 0; i < 640; i++)printf(" ");
		GotoXy(0, 15);
		PutCursor();
		printf("请输入正确选项并按回车确定(或用鼠标直接点击选项):");
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
