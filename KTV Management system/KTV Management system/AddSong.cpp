#include"InfoHandle.h"

bool InfoHandle::judgeExist(const Song &tmp)  //判断待添加歌曲是否已经存在
{
	for (vector<Song>::iterator it = songs.begin(); it != songs.end(); ++it)
	{
		if (it->songName == tmp.songName&&it->singerName == tmp.singerName)
			return true;
	}
	return false;
}

void InfoHandle::addSong()
{
	system("cls");
	Song tmp;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	Draw::drawRect(26, 7, 45, 12);
	Draw::gotoxy(40, 8);
	cout << "***增加歌曲***";
	Draw::gotoxy(28, 10);
	cout << "请输入您要添加的歌曲：";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	Draw::gotoxy(30, 12);
	cout << "歌名：";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	Draw::gotoxy(30, 13);
	cout << "歌手：";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
	Draw::gotoxy(30, 14);
	cout << "歌名拼音缩写：";
	while (1)
	{
		Draw::gotoxy(36, 12);
		cout << "           ";
		Draw::gotoxy(36, 13);
		cout << "           ";
		Draw::gotoxy(44, 14);
		cout << "           ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		Draw::gotoxy(36, 12);
		cin >> tmp.singerName;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		Draw::gotoxy(36, 13);
		cin >> tmp.songName;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
		Draw::gotoxy(44, 14);
		cin >> tmp.songAbbreviation;
		if (judgeExist(tmp))
		{
			Draw::gotoxy(32, 16);
			cout << "歌曲已经存在！请重新添加...";
			Sleep(750);
			Draw::gotoxy(32, 16);
			cout << "                           ";
			Draw::gotoxy(36, 12);
			cout << "                ";
			Draw::gotoxy(36, 13);
			cout << "                ";
			Draw::gotoxy(36, 14);
			cout << "                ";
		}
		else {
			tmp.id = songs.size() + 1;
			tmp.score = 0;
			tmp.status = 1;
			songs.push_back(tmp);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			Draw::gotoxy(32, 16);
			cout << "歌曲添加成功！！！";
			Sleep(750);
			Draw::gotoxy(32, 16);
			cout << "是否继续添加(y/n)：";
			char c;
			while (1)
			{
				cin >> c;
				if (c == 'n')return;
				else if (c == 'y')break;
				else {
					Draw::gotoxy(51, 16);
					cout << "       ";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
					Draw::gotoxy(32, 17);
					cout << "无效指令！请重新输入...";
					Sleep(750);
					Draw::gotoxy(32, 17);
					cout << "                       ";
					Draw::gotoxy(51, 16);
				}
			}
		}
	}
}