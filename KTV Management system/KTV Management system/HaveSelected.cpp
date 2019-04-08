#include"InfoHandle.h"
#include<algorithm>

bool compareSerialNum(const Song &a, const Song &b)
{
	return a.serialNum < b.serialNum;
}

void placeAtTop(int m)   //歌曲置顶
{
	unsigned int n;
	while (1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		Draw::gotoxy(28, 26);
		cout << "输入你想置顶的歌曲序号：   \b\b\b";
		cin >> n;
		if (n > 0 && n <= mySong.size())
		{
			unsigned int i = 0;
			for (; i < 10 && i + m < mySong.size(); ++i) //找到正在播放的歌曲
				if (mySong[i].status == 0)break;
			if (n <= i)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
				Draw::gotoxy(35, 27);
				cout << "置顶失败";
				Sleep(750);
				Draw::gotoxy(35, 27);
				cout << "         ";
				Draw::gotoxy(28, 26);
				cout << "                         ";
				break;
			}
			else {
				mySong[n - 1].serialNum = i + 2;
				for (unsigned int j = i + 1; j < n - 1; j++)
					mySong[j].serialNum++;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
				Draw::gotoxy(35, 27);
				cout << "置顶成功！！！";
				Sleep(750);
				Draw::gotoxy(35, 27);
				cout << "              ";
				Draw::gotoxy(28, 26);
				cout << "                         ";
				break;
			}
		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			Draw::gotoxy(35, 27);
			cout << "歌曲不存在！请重新输入";
			Sleep(750);
			Draw::gotoxy(35, 27);
			cout << "                      ";
		}
	}
}

void giveScore()
{
	unsigned int n;
	while (1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		Draw::gotoxy(28, 26);
		cout << "输入你想评分的歌曲序号(输入0结束)：   \b\b\b";
		cin >> n;
		if (n == 0)
			break;
		if (n > 0 && n <= mySong.size())
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
			Draw::gotoxy(34, 27);
			cout << "输入分数(1-5):     \b\b\b\b\b";
			cin >> mySong[n - 1].score;
			while (mySong[n - 1].score < 1 || mySong[n - 1].score>5)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
				Draw::gotoxy(35, 28);
				cout << "分数不符合要求,请重新输入";
				Sleep(750);
				Draw::gotoxy(35, 28);
				cout << "                         ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
				Draw::gotoxy(34, 27);
				cout << "输入分数(1-5):    \b\b\b\b";
				cin >> mySong[n - 1].score;
			}
			for(auto &s:songs)
				if (s.id == mySong[n - 1].id)
				{
					s.score = mySong[n - 1].score;
					break;
				}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			Draw::gotoxy(35, 28);
			cout << "评分成功！！！";
			Sleep(750);
			Draw::gotoxy(35, 28);
			cout << "              ";
			Draw::gotoxy(28, 26);
			cout << "                                       ";
			Draw::gotoxy(34, 27);
			cout << "                      ";
		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			Draw::gotoxy(35, 27);
			cout << "歌曲不存在！请重新输入";
			Sleep(750);
			Draw::gotoxy(35, 27);
			cout << "                      ";
		}
	}
	Draw::gotoxy(28, 26);    
	cout << "                                         ";
}

void removeSong(int m)
{
	unsigned int n;
	while (1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		Draw::gotoxy(28, 26);
		cout << "输入你想移除的歌曲序号：   \b\b\b";
		cin >> n;
		if (n > 0 && n <= mySong.size())
		{
			if (mySong[n - 1].status == 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
				Draw::gotoxy(35, 27);
				cout << "该歌曲正在播放,移除失败";
				Sleep(750);
				Draw::gotoxy(35, 27);
				cout << "                        ";
			}
			else {
				unsigned int i = 0;
				for (; i < 10 && i + m < mySong.size(); ++i) //找到正在播放的歌曲
					if (mySong[i].status == 0)break;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
				Draw::gotoxy(60, 9 + i);
				cout << mySong[i].singerName << "            ";
				vector<Song>::iterator it = mySong.begin();
				for (; it->serialNum != n; ++it);
				it = mySong.erase(it);
				for (; it != mySong.end(); ++it)
					it->serialNum--;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
				Draw::gotoxy(35, 27);
				cout << "移除成功！！！";
				Sleep(750);
				Draw::gotoxy(35, 27);
				cout << "              ";
				Draw::gotoxy(28, 26);
				cout << "                          ";
				break;
			}
		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			Draw::gotoxy(35, 27);
			cout << "歌曲不存在！请重新输入";
			Sleep(750);
			Draw::gotoxy(35, 27);
			cout << "                      ";
		}
	}
}

void cutTheSong(int m)
{
	unsigned int i = 0;
	for (; i < 10 && i + m + 1< mySong.size(); ++i) //找到正在播放的歌曲
		if (mySong[i].status == 0)
		{
			Draw::gotoxy(60, 9 + i);
			cout << mySong[i].singerName << "           ";
			mySong[i].status = 1;
			break;
		}
	if (i + m + 1== mySong.size())
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		Draw::gotoxy(45, 26);
		cout << "切歌失败！！！";
		Sleep(750);
		Draw::gotoxy(45, 26);
		cout << "                ";
	}
	else {
		mySong[i + 1].status = 0;
		nowTheSong = mySong[i + 1].singerName + "-" + mySong[i + 1].songName;
		cutSongFlag1 = true;
		cutSongFlag2 = true;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
		Draw::gotoxy(45, 26);
		cout << "切歌成功！！！";
		Sleep(750);
		Draw::gotoxy(45, 26);
		cout << "              ";
	}
}

void InfoHandle::haveSelected()
{
	system("cls");
	if (mySong.size() == 0)
	{
		Draw::gotoxy(35, 10);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		cout << "尚未点歌！！！";
		Sleep(750);
		return;
	}
	for (unsigned int i = 0; i < mySong.size(); ++i)
		mySong[i].serialNum = i + 1;
	int count = 1;//第几页
	int m = 0;
	if (mySong.size() % 10 != 0)
		m = 1;
	int sum = mySong.size() / 10 + m;  //共几页
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	Draw::drawRect(26, 7, 54, 16);
	Draw::drawHorizontal(27, 8, 53, '-');
	Draw::gotoxy(28, 21);
	cout << "第 " << count << " 页，共 " << sum << " 页";
	Draw::gotoxy(28, 22);
	cout << "上一页↑，下一页↓，esc返回主页";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	Draw::gotoxy(30, 7);
	cout << "编号";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	Draw::gotoxy(43, 7);
	cout << "歌曲名";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
	Draw::gotoxy(60, 7);
	cout << "歌手名";
	while (1)
	{
		for (int i = 0; i < 10; ++i)
		{
			Draw::gotoxy(30, 9 + i);
			cout << "   ";
			Draw::gotoxy(43, 9 + i);
			cout << "              ";
			Draw::gotoxy(60, 9 + i);
			cout << "     ";
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
		Draw::gotoxy(31, 21);
		cout << count;
		unsigned int n = (count - 1) * 10;
		sort(mySong.begin(), mySong.end(), compareSerialNum);
		for (unsigned int i = 0; i < 10 && i + n < mySong.size(); ++i)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			Draw::gotoxy(30, 9 + i);
			cout << mySong[i + n].serialNum;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
			Draw::gotoxy(43, 9 + i);
			cout << mySong[i + n].songName;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
			Draw::gotoxy(60, 9 + i);
			cout << mySong[i + n].singerName;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
		for (unsigned int i = 0; i < 10 && i + n < mySong.size(); ++i) //显示正在播放的歌曲
			if (mySong[i].status == 0)
			{
				Draw::gotoxy(60, 9 + i);
				cout << mySong[i].singerName << "---正在播放";
				break;
			}
		Draw::gotoxy(28, 24);
		cout << "输入1:置顶歌曲  2:移除歌曲  3:切歌  4:评分";
		int flag = getInput();
		switch (flag)
		{
		case 0:return;
		case 1:if (count > 1)count--; break;
		case 2:if (count > sum)count++; break;
		case 3:placeAtTop(n); break;
		case 4:removeSong(n); break;
		case 5:cutTheSong(n); break;
		case 6:giveScore(); break;
		default:
			break;
		}
	}
}