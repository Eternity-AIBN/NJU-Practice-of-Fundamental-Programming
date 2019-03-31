#include"InfoHandle.h"

int InfoHandle::getInput()
{
	int ch;
	while (1)
	{
		ch = _getch();
		if (ch == 27)return 0; //0��ʾesc
		if (ch == 224)
		{
			ch = _getch();
			if (ch == 72)return 1; //1��ʾ��
			if (ch == 80)return 2; //2��ʾ��
		}
		if (ch > 48 && ch < 53)
			return ch - 46;
	}
}

void InfoHandle::songInquire()
{
	system("cls");
	int count = 1;//�ڼ�ҳ
	int m = 0;
	if (songs.size() % 10 != 0)
		m = 1;
	int sum = songs.size() / 10 + m;  //����ҳ
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	Draw::drawRect(26, 7, 45, 16);
	Draw::drawHorizontal(27, 8, 44, '-');
	Draw::gotoxy(28, 21);
	cout << "�� " << count << " ҳ���� " << sum << " ҳ";
	Draw::gotoxy(28, 22);
	cout << "��һҳ������һҳ����esc������ҳ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	Draw::gotoxy(30, 7);
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	Draw::gotoxy(43, 7);
	cout << "������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
	Draw::gotoxy(60, 7);
	cout << "������";
	while (1)
	{
		for (int i = 0; i < 10; ++i)
		{
			Draw::gotoxy(30, 9 + i);
			cout << "   ";
			Draw::gotoxy(43, 9 + i);
			cout << "              ";
			Draw::gotoxy(60, 9 + i);
			cout << "        ";
		}
		Draw::gotoxy(31, 21);
		cout << count;
		unsigned int n = (count - 1) * 10;
		for (unsigned int i = 0; i < 10 && i + n < songs.size(); ++i)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			Draw::gotoxy(30, 9 + i);
			cout << songs[i + n].id;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
			Draw::gotoxy(43, 9 + i);
			cout << songs[i + n].songName;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
			Draw::gotoxy(60, 9 + i);
			cout << songs[i + n].singerName;
		}
		int flag = getInput();
		if (flag == 0)return;
		if (flag == 1 && count > 1)
			count--;
		if (flag == 2 && count < sum)
			count++;
	}
}