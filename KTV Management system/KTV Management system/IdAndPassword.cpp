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
			cout << "��½�ɹ�������Ϊ����תҳ��...";
			Sleep(750);
			return true;
		}
		times--;
		Draw::gotoxy(32, 14);
		cout << "������󣡻�ʣ" << times << "�λ��ᣡ";
		Sleep(750);
		Draw::gotoxy(38, 12);
		cout << "                   ";
		Draw::gotoxy(32, 14);
		cout << "                           ";
	}
	Draw::gotoxy(38, 14);
	cout << "��½ʧ�ܣ�";
	Sleep(750);
	return false;
}
bool IdAndPassword::checkFormat(const string &s)
{
	if (s.size() > 12)
	{
		Draw::gotoxy(30, 15);
		cout << "���벻�ó���12���ַ���";
		Sleep(750);
		Draw::gotoxy(30, 15);
		cout << "                      ";
		return false;
	}
	unsigned int i = 0, j = 0, k = 0;
	for (; i < s.size(); ++i)    //�ж��������Ƿ�������
		if (isdigit(s[i]))break;
	if (i == s.size())
	{
		Draw::gotoxy(28, 15);
		cout << "��������ɴ�Сд��ĸ,�������";
		Sleep(750);
		Draw::gotoxy(28, 15);
		cout << "                             ";
		return false;
	}
	for (i = 0; i < s.size(); ++i) //�ж��������Ƿ���Сд��ĸ
		if (islower(s[i]))break;
	if (i == s.size())
	{
		Draw::gotoxy(28, 15);
		cout << "��������ɴ�Сд��ĸ,�������";
		Sleep(750);
		Draw::gotoxy(28, 15);
		cout << "                             ";
		return false;
	}
	for (i = 0; i < s.size(); ++i) //�ж��������Ƿ��д�д��ĸ
		if (isupper(s[i]))break;
	if (i == s.size())
	{
		Draw::gotoxy(28, 15);
		cout << "��������ɴ�Сд��ĸ,�������";
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
		if (tmp != passwordNum)  //���������
		{
			times2--;
			Draw::gotoxy(32, 15);
			cout << "�������(ʣ" << times2 << "�λ���)";
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
					if (newPassword == passwordNum)  //�¾�������ͬ
					{
						Draw::gotoxy(30, 15);
						cout << "��ԭ������ͬ������������";
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
					cout << "�������벻һ�£�����������";
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
					cout << "�����޸ĳɹ���";
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
		cout << "�~";
	for (int i = 1; i < 10; ++i)
	{
		Draw::gotoxy(25, 7 + i);
		cout << "�~";
		Draw::gotoxy(59, 7 + i);
		cout << "�~";
	}
	Draw::gotoxy(25, 17);
	for (int i = 0; i < 18; ++i)
		cout << "�~";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
	Draw::gotoxy(35, 9);
	cout << "###�޸�����###";
	Draw::gotoxy(32, 11);
	cout << "�����룺";
	Draw::gotoxy(32, 12);
	cout << "�����룺";
	Draw::gotoxy(32, 13);
	cout << "ȷ�����룺";
}