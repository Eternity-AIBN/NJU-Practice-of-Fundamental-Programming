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
	cout << "***修改歌曲信息***";
	Draw::gotoxy(28, 10);
	cout << "请输入要修改的歌曲ID(输入0退出):";
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
			cout << "歌曲不存在！请重新输入";
			Sleep(750);
			Draw::gotoxy(30, 15);
			cout << "                        ";
		}
		else {
			Draw::gotoxy(28, 12);
			cout << "歌曲信息如下:";
			Draw::gotoxy(34, 13);
			cout << "1.歌名:" << songs[num - 1].songName;
			Draw::gotoxy(34, 14);
			cout << "2.歌手:" << songs[num - 1].singerName;
			Draw::gotoxy(34, 15);
			cout << "3.歌名缩写:" << songs[num - 1].songAbbreviation;
			Draw::gotoxy(28, 16);
			cout << "想修改哪一项:";
			int n;
			while (1) {
				cin >> n;
				if(n<1||n>3)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
					Draw::gotoxy(30, 17);
					cout << "没有该选项！请重新选择";
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