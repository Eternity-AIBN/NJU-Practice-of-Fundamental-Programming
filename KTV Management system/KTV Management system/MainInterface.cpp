#include"MainInterface.h"
#include<iostream>
using namespace std;
void MainInterface::printMain()
{
	system("mode 100,30");
	system("cls");
	Draw::drawFrame(12);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
	Draw::gotoxy(36, 10);
	cout << "=>";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
	Draw::gotoxy(39, 10);
	cout << "0.管理员登陆";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
	Draw::gotoxy(39, 12);
	cout << "1.用户直达";
	Draw::gotoxy(39, 14);
	cout << "2.退出系统";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	Draw::gotoxy(25, 20);
	cout << "PS：方向键↑，↓选择功能，回车键确定.";
}
void MainInterface::printLogin()
{
	system("mode 100,30");
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
	int str;
	int choiceNum = 0;
	while ((str = _getch())!=13) {
		if (str == 224)
		{
			str = _getch();
			if (str == 80|| str == 72)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
				if (choiceNum == 0)
				{
					Draw::gotoxy(36, 10);
					cout << "   0.管理员登陆";
				}
				else if (choiceNum == 1)
				{
					Draw::gotoxy(36, 12);
					cout << "   1.用户直达";
				}
				else if (choiceNum == 2)
				{
					Draw::gotoxy(36, 14);
					cout << "   2.退出系统";
				}
				if (str == 80)
					choiceNum++;
				else choiceNum += 2;
				choiceNum %= 3;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
				Draw::gotoxy(36, 10 + choiceNum * 2);
				cout << "=>";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
				if (choiceNum == 0)
				{
					Draw::gotoxy(39, 10);
					cout << "0.管理员登陆";
				}
				else if (choiceNum == 1)
				{
					Draw::gotoxy(39, 12);
					cout << "1.用户直达";
				}
				else if (choiceNum == 2)
				{
					Draw::gotoxy(39, 14);
					cout << "2.退出系统";
				}
			}
		}
	}
	return choiceNum;
}