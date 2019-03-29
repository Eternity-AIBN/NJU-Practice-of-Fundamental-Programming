#include"IdAndPassword.h"
#include<iostream>
#include<conio.h>
using namespace std;

IdAndPassword::IdAndPassword()
{
	accountNum = "Lihan123456";
	passwordNum = "20010222";
	times = 3;
}
void IdAndPassword::cinPassword(string &s)
{
	s.clear();
	char ch;
	while ((ch = _getch()) != '\r')
	{
		s += ch;
		cout << '*';
	}
}
bool IdAndPassword::judge()
{
	times = 3;
	string inputAccount, inputPassword;
	Draw::gotoxy(38, 11);
	cin >> inputAccount;
	while (times > 0)
	{
		Draw::gotoxy(38, 12);
		cinPassword(inputPassword);
		if (inputAccount == accountNum&&inputPassword == passwordNum)
		{
			Draw::gotoxy(29, 14);
			cout << "登陆成功！即将为您跳转页面...";
			Sleep(750);
			return true;
		}
		times--;
		Draw::gotoxy(32, 14);
		cout << "密码错误！还剩" << times << "次机会！";
		Sleep(750);
		Draw::gotoxy(38, 12);
		cout << "                   ";
		Draw::gotoxy(32, 14);
		cout << "                           ";
	}
	Draw::gotoxy(38, 14);
	cout << "登陆失败！";
	Sleep(750);
	return false;
}
void IdAndPassword::changePassword()
{
	string newPassword, tmp;
	while (1)
	{
		Draw::gotoxy(40, 11);
		cinPassword(tmp);
		if (tmp != passwordNum)  //旧密码错误
		{
			Draw::gotoxy(32, 15);
			cout << "密码错误，请重新输入";
			Sleep(750);
			Draw::gotoxy(32, 15);
			cout << "                    ";
			Draw::gotoxy(40, 11);
			cout << "               ";
		}
		else {
			while (1) {
				while (1)
				{
					Draw::gotoxy(40, 12);
					cinPassword(newPassword);
					if (newPassword != passwordNum)  //新旧密码相同
						break;
					Draw::gotoxy(30, 15);
					cout << "与原密码相同，请重新设置";
					Sleep(750);
					Draw::gotoxy(30, 15);
					cout << "                        ";
					Draw::gotoxy(40, 12);
					cout << "               ";
				}
				Draw::gotoxy(42, 13);
				cinPassword(tmp);
				if (tmp != newPassword)
				{
					Draw::gotoxy(30, 15);
					cout << "两次密码不一致，请重新设置";
					Sleep(750);
					Draw::gotoxy(30, 15);
					cout << "                          ";
					Draw::gotoxy(42, 13);
					cout << "             ";
					Draw::gotoxy(40, 12);
					cout << "               ";

				}
				else {
					Draw::gotoxy(32, 15);
					cout << "密码修改成功！";
					Sleep(750);
					passwordNum = newPassword;
					return;
				}
			}
		}
	}
}
void IdAndPassword::printChange()
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
	Draw::gotoxy(35, 9);
	cout << "###修改密码###";
	Draw::gotoxy(32, 11);
	cout << "旧密码：";
	Draw::gotoxy(32, 12);
	cout << "新密码：";
	Draw::gotoxy(32, 13);
	cout << "确认密码：";
}