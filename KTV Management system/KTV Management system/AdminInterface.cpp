#include"AdminInterface.h"
#include<iostream>
using namespace std;
void AdminInterface::printAdmin()
{
	system("cls");
	Draw::drawFrame(14);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
	Draw::gotoxy(39, 10);
	cout << "0.������Ϣ��ѯ";
	Draw::gotoxy(39, 11);
	cout << "1.���Ӹ���";
	Draw::gotoxy(39, 12);
	cout << "2.��������";
	Draw::gotoxy(39, 13);
	cout << "3.ɾ������";
	Draw::gotoxy(39, 14);
	cout << "4.�޸ĸ�����Ϣ";
	Draw::gotoxy(39, 15);
	cout << "5.��������";
	Draw::gotoxy(39, 16);
	cout << "6.�޸�����";
	Draw::gotoxy(39, 17);
	cout << "7.����������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	Draw::gotoxy(25, 22);
	cout << "������ѡ�";
}
int AdminInterface::adminChoice()
{
	int n;
	while (1) {
		Draw::gotoxy(37, 22);
		cin >> n;
		if (n < 0 || n > 7)
		{
			Draw::gotoxy(30, 23);
			cout << "û�д�ѡ�������ѡ��...";
			Sleep(1000);
			Draw::gotoxy(30, 23);
			cout << "                         ";
			Draw::gotoxy(37, 22);
			cout << "             ";
		}
		else break;
	}
	return n;
}