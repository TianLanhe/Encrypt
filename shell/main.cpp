#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#include "core/Encrypt.h"
#include "core/PasswordManager.h"
#include "UI.h"

#define ENCRYPT 0
#define DECRYPT 1
void PrintMenu();
//打印主菜单
void PrintLogin();

void PrintMenu(){
	printf("\n");
        printf("            ┌─────────欢迎使用加密解密程序──────┐              \n");
        printf("            │  ┌─────────────────────┐  │              \n");
        printf("            │  │                                          │  │              \n");
        printf("            │  │无论文本图片视频音频，都能加加加解解解.   │  │              \n");
        printf("            │  │密码随便设，就是别忘了. ^_^               │  │              \n");
        printf("            │  │3.0版本来了，优化了界面，输入可带空格     │  │              \n");
        printf("            │  │鼠标键盘都可以操作.(＾－＾)V              │  │              \n");
        printf("            │  └─────────────────────┘  │              \n");
        printf("            │                                                  │              \n");
        printf("            │              请选择： 1. 文件加密                │              \n");
        printf("            │                       2. 文件解密                │              \n");
        printf("            │                       3. 退出程序                │              \n");
        printf("            │                                                  │              \n");
        printf("            └─────────────────────────┘              \n");
}
void PrintLogin(){
	printf("\n");
        printf("            ┌─────────欢迎使用加密解密程序──────┐              \n");
        printf("            │                                                  │              \n");
        printf("            │    程序设置了密码，请输入密码后使用.             │              \n");
        printf("            │                                                  │              \n");
        printf("            │              请选择： 1. 输入密码                │              \n");
        printf("            │                       2. 退出程序                │              \n");
        printf("            │                                                  │              \n");
        printf("            └─────────────────────────┘              \n");
}
void Encrypt(int a){    					 		  //加密与解密文件
	FILE *fin,*fout;                        //fin为读入的需加密文件，fout为将保存的已加密文件
	int count,i,length;                     //count用于每次读取的实际字节数，i是循环变量，length是密码的长度
	char buffer[16];                        //用于暂时存放读取的数据
	char filename1[30],filename2[30];       //filename1为需加密文件名，filename2为已加密文件名
	char password[16],pas_check[16];        //password为加密的密码,pas_check为第二次输入检测密码是否一致
	char *p;								//确定是 加密 还是 解密
	int n,X,Y,type;                         //n是循环变量，X Y为坐标，type为键盘操作或鼠标操作
	HANDLE hInput;                                       /*获取标准输入设备句柄*/
    INPUT_RECORD inRec;                                 /* 返回数据记录 */
    DWORD res;                                         /* 返回已读取的记录数 */
    hInput = GetStdHandle(STD_INPUT_HANDLE);
	PutCursor();
	if(a==0)p="加密";
	else p="解密";
	do{
		GotoXy(0,15);
		for(n=0;n<640;n++)printf(" ");
		GotoXy(0,15);
		printf("请输入要%s的文件名及其路径：",p);
		gets(filename1);
		while((fin=fopen(filename1,"rb"))==NULL){
			printf("无法打开 \"%s\" ,可能路径与文件名有误,请重新输入（输入0返回菜单）：",filename1);
			gets(filename1);
			if(!(strcmp(filename1,"0"))){
				fclose(fin);
				return;
			}
		}
		printf("请输入%s后的文件名及其路径：",p);
		gets(filename2);
		while(fopen(filename2,"r")!=NULL){
			if(!(strcmp(filename2,filename1)))printf("%s后的文件名不能与原文件名相同，请重新输入:",p);
			else printf("%s已存在，请重新输入:",filename2);
			gets(filename2);
		}
		while((fout=fopen(filename2,"wb"))==NULL){
			printf("无法创建 \"%s\" ,请重新输入（输入0返回菜单）：",filename2);
			gets(filename2);
			if(!(strcmp(filename2,"0"))){
				fclose(fin);
				fclose(fout);
				return;
			}
		}
		do{
			printf("请输入%s的密码(不长于15位任意字符)：",p);
			gets(password);
			while((length=strlen(password))>15){
				printf("对不起，密码长于15位，请重新输入（输入0返回菜单）：");
				fflush(stdin);
				gets(password);
				if(!(strcmp(password,"0"))){
					fclose(fin);
					fclose(fout);
					return;
				}
			}
			strcpy(pas_check,password);
			if(!a){
				printf("请再次输入%s的密码：",p);
				gets(pas_check);
				if(strcmp(password,pas_check))printf("两次输入的密码不一致，请重新输入！\n");
			}
		}while(strcmp(password,pas_check));
		printf("正在%s...",p);
		while((count=fread(buffer,1,length,fin))>0){
			for(i=0;i<count;i++)buffer[i]^=password[i];
			fwrite(buffer,1,count,fout);
		}
		GotoXy(0,15);
		for(n=0;n<640;n++)printf(" ");
		GotoXy(0,15);
		printf("文件 \"%s\" %s成功，保存在 \"%s\" ！\n\n",filename1,p,filename2);
		fclose(fin);
		fclose(fout);
		HideCursor();
		printf("接下来你希望：\n");
		printf("1.继续当前操作.\n");
		printf("2.返回主菜单.\n");
		printf("3.退出程序.\n");
		Y=0;
		type=GetXy(&X,&Y,0,14,18,20);
		if(type!=1){
			printf("%c",type);
			getch();
		}
		if(Y==20||type=='3')exit(0);
	}while(Y==18||type=='1');
}
void GotoXy(int x,int y){
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
int GetXy(int *X,int *Y,int x1,int x2,int y1,int y2){
	HANDLE hInput;                              //获取标准输入设备句柄
    INPUT_RECORD inRec;                         //返回数据记录
    DWORD res;                                  //返回已读取的记录数
    int x=-1,y=-1;
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	do{
		ReadConsoleInput(hInput, &inRec, 1, &res);
		if(inRec.EventType==MOUSE_EVENT&&inRec.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED){
			x=(int)inRec.Event.MouseEvent.dwMousePosition.X;
			y=(int)inRec.Event.MouseEvent.dwMousePosition.Y;
		}else if(inRec.EventType==KEY_EVENT)return inRec.Event.KeyEvent.uChar.AsciiChar;
	}while(!(x>=x1&&x<=x2&&y>=y1&&y<=y2));
	*X=x;
	*Y=y;
	return 1;
}

int main(){
        UIControler ui;

        ui.Start();
        while(ui.GetReturnCode() != UI::Stop)
            ui.Transform(ui.GetReturnCode());

        return 0;

	int i,*hint;                       //循环变量i，密码提示hint[4]
	int X=0,Y=0;					   //记录鼠标点击的坐标
	char *password;					   //正确密码password
	int type;
	PrintLogin();                      //打印登录界面
	printf("请输入正确选项并按回车确定(或用鼠标直接点击选项):");
	while(1){
		type=GetXy(&X,&Y,40,47,5,6);
		if(type==1){
			if(Y==5){
				GotoXy(0,9);
				for(i=0;i<79;i++)printf(" ");
				GotoXy(0,9);
				hint=setHint();
				password=setPassword(hint);
				printf("密码提示：");
				for(i=0;i<4;i++)printf("%c",hint[i]);
				printf("\n");
				if(isPassword(password)){
					Y=0;
					X=0;
					printf("密码正确！(按任意键进入菜单)\n");
					HideCursor();
					free(hint);
					free(password);
					hint=NULL;
					password=NULL;
					getch();
					break;
				}else return 0;
			}else if(Y==6){
				GotoXy(28,12);
				HideCursor();
				return 0;
			}
		}else{
			char temp;
			if(type=='1'||type=='2'){
				printf("%c",type);
				do{
					temp=getch();
				}while(temp!=13);
				printf("\n");
			}
			if(type=='2'){
				GotoXy(28,12);
				HideCursor();
				return 0;
			}
			else if(type=='1'){
				hint=setHint();
				password=setPassword(hint);
				printf("密码提示：");
				for(i=0;i<4;i++)printf("%c",hint[i]);
				printf("\n");
				if(isPassword(password)){
					Y=0;
					X=0;
					printf("密码正确！(按任意键进入菜单)\n");
					HideCursor();
					getch();
					break;
				}else{
					GotoXy(28,12);
					HideCursor();
					free(hint);
					free(password);
					return 0;
				}
			}
		}
	}
	GetXy(&X,&Y,40,47,10,12);
	while(1){
/*注意这里不能用清屏函数system("cls")，会无法读取鼠标事件，我也不知道为什么，交给未来的我吧*/
		GotoXy(0,0);
		PrintMenu();        			   //打印菜单
		for(i=0;i<640;i++)printf(" ");
		GotoXy(0,15);
		PutCursor();
		printf("请输入正确选项并按回车确定(或用鼠标直接点击选项):");
		type=GetXy(&X,&Y,40,47,10,12);
		if(type==1){
			GotoXy(0,15);
			for(i=0;i<79;i++)printf(" ");
			GotoXy(0,15);
			switch(Y){
			case 10:Encrypt(ENCRYPT);break;
			case 11:Encrypt(DECRYPT);break;
			case 12:GotoXy(28,16);
					 HideCursor();
					 return 0;
			}
			X=0;
			Y=0;
		}else{
			if(type=='1'||type=='2'||type=='3')printf("%c",type);
			getch();
			switch(type){
			case '1':Encrypt(ENCRYPT);break;
			case '2':Encrypt(DECRYPT);break;
			case '3':return 0;
			}
		}
	}
	return 0;
}
