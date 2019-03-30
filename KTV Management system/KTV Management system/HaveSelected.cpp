#include"InfoHandle.h"
#include<algorithm>

bool compareSerialNum(const Song &a, const Song &b)
{
	return a.serialNum > b.serialNum;
}

void placeAtTop()   //歌曲置顶
{
	int n;
	Draw::gotoxy(28, 27);
	cout << "输入你想置顶的歌曲序号：";
	while (1) {
		cin >> n;
		if (n > 0 && n <= mySong.size())
		{
			mySong[n - 1].status = 0;
			mySong[0].status = 1;
			mySong[n - 1].serialNum = 1;
			for (int i = 0; i < n - 1; i++)
				mySong[i].serialNum++;
			Draw::gotoxy(35, 28);
			cout << "置顶成功！！！";
			Sleep(750);
			Draw::gotoxy(35, 28);
			cout << "              ";
			break;
		}
		else {
			Draw::gotoxy(35, 28);
			cout << "歌曲不存在！请重新输入";
			Sleep(750);
			Draw::gotoxy(35, 28);
			cout << "                      ";
			Draw::gotoxy(28, 27);
			cout << "输入你想置顶的歌曲序号：   \b\b\b";
		}
	}
}

void removeSong()
{
	int n;
	Draw::gotoxy(28, 27);
	cout << "输入你想移除的歌曲序号：";
	while (1) {
		cin >> n;
		if (n > 0 && n <= mySong.size())
		{
			vector<Song>::iterator it = songs.begin();
			for (; it->serialNum != n; ++it);
			it = songs.erase(it);
			for (; it != songs.end(); ++it)
				it->serialNum--;
			Draw::gotoxy(35, 28);
			cout << "移除成功！！！";
			Sleep(750);
			Draw::gotoxy(35, 28);
			cout << "              ";
			break;
		}
		else {
			Draw::gotoxy(35, 28);
			cout << "歌曲不存在！请重新输入";
			Sleep(750);
			Draw::gotoxy(35, 28);
			cout << "                      ";
			Draw::gotoxy(28, 27);
			cout << "输入你想移除的歌曲序号：   \b\b\b";
		}
	}
}

void cutTheSong()
{
	vector<Song>::iterator it = songs.begin();
	it = songs.erase(it);
	for (; it != songs.end(); ++it)
		it->serialNum--;
	Draw::gotoxy(35, 28);
	cout << "切歌成功！！！";
	Sleep(750);
	Draw::gotoxy(35, 28);
	cout << "              ";
}

void InfoHandle::haveSelected()
{
	system("cls");
	for (int i = 0; i < mySong.size(); ++i)
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
		Draw::gotoxy(60, 9);
		cout << mySong[n].singerName << "---正在播放";
		int flag = getInput();
		switch (flag)
		{
		case 0:return;
		case 1:if (count > 1)count--; break;
		case 2:if (count > sum)count++; break;
		case 3:placeAtTop(); break;
		case 4:removeSong(); break;
		case 5:cutTheSong(); break;
		default:
			break;
		}
	}
}