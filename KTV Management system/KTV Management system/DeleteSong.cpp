#include"InfoHandle.h"

void InfoHandle::deleteSong()
{
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	Draw::drawRect(26, 7, 45, 12);
	Draw::gotoxy(40, 8);
	cout << "***ɾ������***";
	int num;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	Draw::gotoxy(28, 10);
	cout << "����Ҫɾ�������ı��(����0����):";
	while (1) {
		Draw::gotoxy(61, 10);
		cout << "        ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
		Draw::gotoxy(61, 10);
		cin >> num;
		if (num == 0)return;
		if (num<0 || num>(int)songs.size())
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			Draw::gotoxy(30, 15);
			cout << "���������ڣ�����������";
			Sleep(750);
			Draw::gotoxy(30, 15);
			cout << "                        ";
		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
			Draw::gotoxy(30, 12);
			cout << "ȷ��Ҫɾ����(y/n):";
			char c;
			while (1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
				cin >> c;
				if (c == 'n')break;
				else if (c == 'y') {
					vector<Song>::iterator it = songs.begin();
					for (; it->id != num; ++it);
					it = songs.erase(it);
					for (; it != songs.end(); ++it)
						it->id--;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
					Draw::gotoxy(34, 14);
					cout << "ɾ���ɹ�������";
					Sleep(750);
					Draw::gotoxy(34, 14);
					cout << "              ";
					break;
				}
				else {
					Draw::gotoxy(48, 12); 
					cout << "       ";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
					Draw::gotoxy(32, 14);
					cout << "��Чָ�����������...";
					Sleep(250);
					Draw::gotoxy(32, 14);
					cout << "                       ";
					Draw::gotoxy(48, 12);
				}
			}
			Draw::gotoxy(28, 12);
			cout << "                         ";
		}
	}
}