#include"InfoHandle.h"

void modifySongName(int num)
{
	Draw::gotoxy(28, 17);
	cout << "�����µĸ���:";
	cin >> songs[num - 1].songName;
}
void modifySingerName(int num)
{
	Draw::gotoxy(28, 17);
	cout << "�����µĸ�����:";
	cin >> songs[num - 1].singerName;
}
void modifySongAbbreviation(int num)
{
	Draw::gotoxy(28, 17);
	cout << "�����µĸ�����д:";
	cin >> songs[num - 1].songAbbreviation;
}

void InfoHandle::modifyInfo()
{
	system("cls");
	int num;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	Draw::drawRect(26, 7, 45, 12);
	Draw::gotoxy(40, 7);
	cout << "***�޸ĸ�����Ϣ***";
	Draw::gotoxy(28, 10);
	cout << "������Ҫ�޸ĵĸ���ID(����0�˳�):";
	while (1)
	{
		Draw::gotoxy(61, 10);
		cout << "        ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		Draw::gotoxy(61, 10);
		cin >> num;
		if (num == 0)return;
		if (num<0 || num>(int)songs.size())
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			Draw::gotoxy(34, 15);
			cout << "���������ڣ�����������";
			Sleep(750);
			Draw::gotoxy(34, 15);
			cout << "                        ";
		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
			Draw::gotoxy(28, 12);
			cout << "������Ϣ����:";
			Draw::gotoxy(34, 13);
			cout << "1.����:" << songs[num - 1].songName;
			Draw::gotoxy(34, 14);
			cout << "2.����:" << songs[num - 1].singerName;
			Draw::gotoxy(34, 15);
			cout << "3.������д:" << songs[num - 1].songAbbreviation;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
			Draw::gotoxy(28, 16);
			cout << "���޸���һ��:";
			int n;
			while (1) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
				Draw::gotoxy(42, 16);
				cout << "       ";
				Draw::gotoxy(42, 16);
				cin >> n;
				if(n<1||n>3)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
					Draw::gotoxy(30, 17);
					cout << "û�и�ѡ�������ѡ��";
					Sleep(750);
					Draw::gotoxy(30, 17);
					cout << "                        ";
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
					if (n == 1)modifySongName(num);
					if (n == 2)modifySingerName(num);
					if (n == 3)modifySongAbbreviation(num);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
					Draw::gotoxy(34, 18);
					cout << "�޸ĳɹ�������";
					Sleep(0);
					for (int i = 0; i < 7; ++i)
					{
						Draw::gotoxy(28, 12 + i);
						cout << "                                ";
					}
					break;
				}
			}
		}
	}
}