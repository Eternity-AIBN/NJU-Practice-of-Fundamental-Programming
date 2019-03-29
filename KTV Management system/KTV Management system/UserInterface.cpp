#include"UserInterface.h"
#include<iostream>
using namespace std;
void UserInterface::printUser()
{
	system("cls");
	Draw::drawFrame(12);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
	Draw::gotoxy(39, 10);
	cout << "0.歌手点歌";
	Draw::gotoxy(39, 11);
	cout << "1.歌名点歌";
	Draw::gotoxy(39, 12);
	cout << "2.拼音点歌";
	Draw::gotoxy(39, 13);
	cout << "3.已点歌曲";
	Draw::gotoxy(39, 14);
	cout << "4.切歌";
	Draw::gotoxy(39, 15);
	cout << "5.返回主界面";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	Draw::gotoxy(25, 20);
	cout << "请输入选项：";
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
			cout << "没有此选项，请重新选择...";
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