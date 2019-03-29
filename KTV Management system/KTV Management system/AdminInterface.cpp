#include"AdminInterface.h"
#include<iostream>
using namespace std;
void AdminInterface::printAdmin()
{
	system("cls");
	Draw::drawFrame(14);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
	Draw::gotoxy(39, 10);
	cout << "0.歌曲信息查询";
	Draw::gotoxy(39, 11);
	cout << "1.增加歌曲";
	Draw::gotoxy(39, 12);
	cout << "2.批量导入";
	Draw::gotoxy(39, 13);
	cout << "3.删除歌曲";
	Draw::gotoxy(39, 14);
	cout << "4.修改歌曲信息";
	Draw::gotoxy(39, 15);
	cout << "5.歌曲排行";
	Draw::gotoxy(39, 16);
	cout << "6.修改密码";
	Draw::gotoxy(39, 17);
	cout << "7.返回主界面";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	Draw::gotoxy(25, 22);
	cout << "请输入选项：";
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
			cout << "没有此选项，请重新选择...";
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