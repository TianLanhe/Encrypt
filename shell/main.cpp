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
//��ӡ���˵�
void PrintLogin();

void PrintMenu(){
	printf("\n");
        printf("            ����������������������ӭʹ�ü��ܽ��ܳ��򩤩�����������              \n");
        printf("            ��  ����������������������������������������������  ��              \n");
        printf("            ��  ��                                          ��  ��              \n");
        printf("            ��  �������ı�ͼƬ��Ƶ��Ƶ�����ܼӼӼӽ���.   ��  ��              \n");
        printf("            ��  ����������裬���Ǳ�����. ^_^               ��  ��              \n");
        printf("            ��  ��3.0�汾���ˣ��Ż��˽��棬����ɴ��ո�     ��  ��              \n");
        printf("            ��  �������̶����Բ���.(�ޣ���)V              ��  ��              \n");
        printf("            ��  ����������������������������������������������  ��              \n");
        printf("            ��                                                  ��              \n");
        printf("            ��              ��ѡ�� 1. �ļ�����                ��              \n");
        printf("            ��                       2. �ļ�����                ��              \n");
        printf("            ��                       3. �˳�����                ��              \n");
        printf("            ��                                                  ��              \n");
        printf("            ������������������������������������������������������              \n");
}
void PrintLogin(){
	printf("\n");
        printf("            ����������������������ӭʹ�ü��ܽ��ܳ��򩤩�����������              \n");
        printf("            ��                                                  ��              \n");
        printf("            ��    �������������룬�����������ʹ��.             ��              \n");
        printf("            ��                                                  ��              \n");
        printf("            ��              ��ѡ�� 1. ��������                ��              \n");
        printf("            ��                       2. �˳�����                ��              \n");
        printf("            ��                                                  ��              \n");
        printf("            ������������������������������������������������������              \n");
}
void Encrypt(int a){    					 		  //����������ļ�
	FILE *fin,*fout;                        //finΪ�����������ļ���foutΪ��������Ѽ����ļ�
	int count,i,length;                     //count����ÿ�ζ�ȡ��ʵ���ֽ�����i��ѭ��������length������ĳ���
	char buffer[16];                        //������ʱ��Ŷ�ȡ������
	char filename1[30],filename2[30];       //filename1Ϊ������ļ�����filename2Ϊ�Ѽ����ļ���
	char password[16],pas_check[16];        //passwordΪ���ܵ�����,pas_checkΪ�ڶ��������������Ƿ�һ��
	char *p;								//ȷ���� ���� ���� ����
	int n,X,Y,type;                         //n��ѭ��������X YΪ���꣬typeΪ���̲�����������
	HANDLE hInput;                                       /*��ȡ��׼�����豸���*/
    INPUT_RECORD inRec;                                 /* �������ݼ�¼ */
    DWORD res;                                         /* �����Ѷ�ȡ�ļ�¼�� */
    hInput = GetStdHandle(STD_INPUT_HANDLE);
	PutCursor();
	if(a==0)p="����";
	else p="����";
	do{
		GotoXy(0,15);
		for(n=0;n<640;n++)printf(" ");
		GotoXy(0,15);
		printf("������Ҫ%s���ļ�������·����",p);
		gets(filename1);
		while((fin=fopen(filename1,"rb"))==NULL){
			printf("�޷��� \"%s\" ,����·�����ļ�������,���������루����0���ز˵�����",filename1);
			gets(filename1);
			if(!(strcmp(filename1,"0"))){
				fclose(fin);
				return;
			}
		}
		printf("������%s����ļ�������·����",p);
		gets(filename2);
		while(fopen(filename2,"r")!=NULL){
			if(!(strcmp(filename2,filename1)))printf("%s����ļ���������ԭ�ļ�����ͬ������������:",p);
			else printf("%s�Ѵ��ڣ�����������:",filename2);
			gets(filename2);
		}
		while((fout=fopen(filename2,"wb"))==NULL){
			printf("�޷����� \"%s\" ,���������루����0���ز˵�����",filename2);
			gets(filename2);
			if(!(strcmp(filename2,"0"))){
				fclose(fin);
				fclose(fout);
				return;
			}
		}
		do{
			printf("������%s������(������15λ�����ַ�)��",p);
			gets(password);
			while((length=strlen(password))>15){
				printf("�Բ������볤��15λ�����������루����0���ز˵�����");
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
				printf("���ٴ�����%s�����룺",p);
				gets(pas_check);
				if(strcmp(password,pas_check))printf("������������벻һ�£����������룡\n");
			}
		}while(strcmp(password,pas_check));
		printf("����%s...",p);
		while((count=fread(buffer,1,length,fin))>0){
			for(i=0;i<count;i++)buffer[i]^=password[i];
			fwrite(buffer,1,count,fout);
		}
		GotoXy(0,15);
		for(n=0;n<640;n++)printf(" ");
		GotoXy(0,15);
		printf("�ļ� \"%s\" %s�ɹ��������� \"%s\" ��\n\n",filename1,p,filename2);
		fclose(fin);
		fclose(fout);
		HideCursor();
		printf("��������ϣ����\n");
		printf("1.������ǰ����.\n");
		printf("2.�������˵�.\n");
		printf("3.�˳�����.\n");
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
	HANDLE hInput;                              //��ȡ��׼�����豸���
    INPUT_RECORD inRec;                         //�������ݼ�¼
    DWORD res;                                  //�����Ѷ�ȡ�ļ�¼��
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

	int i,*hint;                       //ѭ������i��������ʾhint[4]
	int X=0,Y=0;					   //��¼�����������
	char *password;					   //��ȷ����password
	int type;
	PrintLogin();                      //��ӡ��¼����
	printf("��������ȷѡ����س�ȷ��(�������ֱ�ӵ��ѡ��):");
	while(1){
		type=GetXy(&X,&Y,40,47,5,6);
		if(type==1){
			if(Y==5){
				GotoXy(0,9);
				for(i=0;i<79;i++)printf(" ");
				GotoXy(0,9);
				hint=setHint();
				password=setPassword(hint);
				printf("������ʾ��");
				for(i=0;i<4;i++)printf("%c",hint[i]);
				printf("\n");
				if(isPassword(password)){
					Y=0;
					X=0;
					printf("������ȷ��(�����������˵�)\n");
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
				printf("������ʾ��");
				for(i=0;i<4;i++)printf("%c",hint[i]);
				printf("\n");
				if(isPassword(password)){
					Y=0;
					X=0;
					printf("������ȷ��(�����������˵�)\n");
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
/*ע�����ﲻ������������system("cls")�����޷���ȡ����¼�����Ҳ��֪��Ϊʲô������δ�����Ұ�*/
		GotoXy(0,0);
		PrintMenu();        			   //��ӡ�˵�
		for(i=0;i<640;i++)printf(" ");
		GotoXy(0,15);
		PutCursor();
		printf("��������ȷѡ����س�ȷ��(�������ֱ�ӵ��ѡ��):");
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
