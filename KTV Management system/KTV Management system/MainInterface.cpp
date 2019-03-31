#include"MainInterface.h"
#include<iostream>
using namespace std;
void MainInterface::printMain()
{
	system("cls");
	Draw::drawFrame(10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
	Draw::gotoxy(39, 10);
	cout << "0.管理员登陆";
	Draw::gotoxy(39, 11);
	cout << "1.用户直达";
	Draw::gotoxy(39, 12);
	cout << "2.退出系统";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	Draw::gotoxy(25, 18);
	cout << "请输入选项：";
}
void MainInterface::printLogin()
{
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	Draw::gotoxy(25, 7);
	for (int i = 0; i < 18; ++i)
		cout << "▇";
	for (int i = 1; i < 10; ++i)
	{
		Draw::gotoxy(25, 7 + i);
		cout << "▇";
		Draw::gotoxy(59, 7 + i);
		cout << "▇";
	}
	Draw::gotoxy(25, 17);
	for (int i = 0; i < 18; ++i)
		cout << "▇";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	Draw::gotoxy(35, 9);
	cout << "###管理员登陆###";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
	Draw::gotoxy(32, 11);
	cout << "账号：";
	Draw::gotoxy(32, 12);
	cout << "密码：";
}
int MainInterface::mainChoice()
{
	int n;
	while (1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
		Draw::gotoxy(37, 18);
		cin >> n;
		if (n < 0 || n > 2)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			Draw::gotoxy(30, 19);
			cout << "没有此选项，请重新选择...";
			Sleep(1000);
			Draw::gotoxy(30, 19);
			cout << "                         ";
			Draw::gotoxy(37, 18);
			cout << "               ";
		}
		else break;
	}
	return n;
}