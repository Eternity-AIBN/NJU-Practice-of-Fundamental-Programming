#include"UserInterface.h"
#include<iostream>
using namespace std;
void UserInterface::printUser()
{
	system("cls");
	Draw::drawFrame(12);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
	Draw::gotoxy(39, 10);
	cout << "0.���ֵ��";
	Draw::gotoxy(39, 11);
	cout << "1.�������";
	Draw::gotoxy(39, 12);
	cout << "2.ƴ�����";
	Draw::gotoxy(39, 13);
	cout << "3.�ѵ����";
	Draw::gotoxy(39, 14);
	cout << "4.�и�";
	Draw::gotoxy(39, 15);
	cout << "5.����������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	Draw::gotoxy(25, 20);
	cout << "������ѡ�";
}
int UserInterface::userChoice()
{
	int n;
	while (1) {
		Draw::gotoxy(37, 20);
		cin >> n;
		if (n < 0 || n > 5)
		{
			Draw::gotoxy(30, 21);
			cout << "û�д�ѡ�������ѡ��...";
			Sleep(1000);
			Draw::gotoxy(30, 21);
			cout << "                         ";
			Draw::gotoxy(37, 20);
			cout << "             ";
		}
		else break;
	}
	return n;
}