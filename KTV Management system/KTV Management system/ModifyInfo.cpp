#include"InfoHandle.h"

void modifySongName(int num)
{

}
void modifySingerName(int num)
{

}
void modifySongAbbreviation(int num)
{

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
			Draw::gotoxy(28, 12);
			cout << "������Ϣ����:";
			Draw::gotoxy(34, 13);
			cout << "1.����:" << songs[num - 1].songName;
			Draw::gotoxy(34, 14);
			cout << "2.����:" << songs[num - 1].singerName;
			Draw::gotoxy(34, 15);
			cout << "3.������д:" << songs[num - 1].songAbbreviation;
			Draw::gotoxy(28, 16);
			cout << "���޸���һ��:";
			int n;
			while (1) {
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

				}
			}
		}
	}
}