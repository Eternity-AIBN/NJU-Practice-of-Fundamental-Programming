#include"InfoHandle.h"
#include<algorithm>

bool compareScore(const Song &a, const Song &b)
{
	return a.score > b.score;
}

void InfoHandle::songRanking()
{
	system("cls");
	int count = 1;//�ڼ�ҳ
	int m = 0;
	if (songs.size() % 10 != 0)
		m = 1;
	int sum = songs.size() / 10 + m;  //����ҳ
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	Draw::drawRect(26, 7, 55, 16);
	Draw::drawHorizontal(27, 8, 54, '-');
	Draw::gotoxy(28, 21);
	cout << "�� " << count << " ҳ���� " << sum << " ҳ";
	Draw::gotoxy(28, 22);
	cout << "��һҳ������һҳ����esc������ҳ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	Draw::gotoxy(30, 7);
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	Draw::gotoxy(43, 7);
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	Draw::gotoxy(53, 7);
	cout << "������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
	Draw::gotoxy(70, 7);
	cout << "������";
	sort(songs.begin(), songs.end(), compareScore);
	while (1)
	{
		for (int i = 0; i < 10; ++i)
		{
			Draw::gotoxy(30, 9 + i);
			cout << "   ";
			Draw::gotoxy(43, 9 + i);
			cout << "   ";
			Draw::gotoxy(53, 9 + i);
			cout << "              ";
			Draw::gotoxy(70, 9 + i);
			cout << "     ";
		}
		Draw::gotoxy(31, 21);
		cout << count;
		unsigned int n = (count - 1) * 10;
		for (unsigned int i = 0; i < 10 && i + n < songs.size(); ++i)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			Draw::gotoxy(30, 9 + i);
			cout << songs[i + n].score;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			Draw::gotoxy(43, 9 + i);
			cout << songs[i + n].id;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
			Draw::gotoxy(53, 9 + i);
			cout << songs[i + n].songName;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
			Draw::gotoxy(70, 9 + i);
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