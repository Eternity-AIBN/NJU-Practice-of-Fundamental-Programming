#include"IdAndPassword.h"
#include<iostream>
#include<conio.h>
using namespace std;

IdAndPassword::IdAndPassword()
{
	accountNum = "Lihan123";
	passwordNum = "Li123";
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
bool IdAndPassword::checkFormat(const string &s)
{
	if (s.size() > 12)
	{
		Draw::gotoxy(30, 15);
		cout << "密码不得超过12个字符！";
		Sleep(750);
		Draw::gotoxy(30, 15);
		cout << "                      ";
		return false;
	}
	unsigned int i = 0, j = 0, k = 0;
	for (; i < s.size(); ++i)    //判断密码中是否有数字
		if (isdigit(s[i]))break;
	if (i == s.size())
	{
		Draw::gotoxy(28, 15);
		cout << "密码必须由大小写字母,数字组成";
		Sleep(750);
		Draw::gotoxy(28, 15);
		cout << "                             ";
		return false;
	}
	for (i = 0; i < s.size(); ++i) //判断密码中是否有小写字母
		if (islower(s[i]))break;
	if (i == s.size())
	{
		Draw::gotoxy(28, 15);
		cout << "密码必须由大小写字母,数字组成";
		Sleep(750);
		Draw::gotoxy(28, 15);
		cout << "                             ";
		return false;
	}
	for (i = 0; i < s.size(); ++i) //判断密码中是否有大写字母
		if (isupper(s[i]))break;
	if (i == s.size())
	{
		Draw::gotoxy(28, 15);
		cout << "密码必须由大小写字母,数字组成";
		Sleep(750);
		Draw::gotoxy(28, 15);
		cout << "                             ";
		return false;
	}
	return true;
}
void IdAndPassword::changePassword()
{
	string newPassword, tmp;
	int times2 = 3;
	while (1)
	{
		Draw::gotoxy(40, 11);
		cinPassword(tmp);
		if (tmp != passwordNum)  //旧密码错误
		{
			times2--;
			Draw::gotoxy(32, 15);
			cout << "密码错误，(剩" << times2 << "次机会)";
			Sleep(750);
			Draw::gotoxy(32, 15);
			cout << "                           ";
			Draw::gotoxy(40, 11);
			cout << "               ";
			if (times2 == 0)return;
		}
		else {
			while (1) {
				while (1)
				{
					Draw::gotoxy(40, 12);
					cinPassword(newPassword);
					if (newPassword == passwordNum)  //新旧密码相同
					{
						Draw::gotoxy(30, 15);
						cout << "与原密码相同，请重新设置";
						Sleep(750);
						Draw::gotoxy(30, 15);
						cout << "                        ";
						Draw::gotoxy(40, 12);
						cout << "               ";
					}
					else if (checkFormat(newPassword))
						break;
					else {
						Draw::gotoxy(40, 12);
						cout << "               ";
					}
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