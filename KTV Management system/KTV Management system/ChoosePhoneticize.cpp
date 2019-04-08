#include"InfoHandle.h"

void InfoHandle::judgeSongPhoneticize(vector<Song> &findSong, const string &s)
{
	findSong.clear();
	for (auto song2 : songs)
		if (song2.songAbbreviation.find(s) != string::npos)
			findSong.push_back(song2);
}

void InfoHandle::choosePhoneticize()
{
	system("cls");
	string name;
	vector<Song> findSong;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	Draw::drawRect(26, 7, 45, 14);
	Draw::gotoxy(40, 8);
	cout << "***拼音点歌***";
	Draw::gotoxy(28, 10);
	cout << "输入要查找的拼音(end结束)：";
	while (1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
		Draw::gotoxy(55, 10);
		cout << "        ";
		Draw::gotoxy(55, 10);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cin >> name;
		if (name == "end")return;
		judgeSongPhoneticize(findSong, name);
		if (findSong.size() == 0)  //歌曲不存在
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			Draw::gotoxy(32, 15);
			cout << "该歌曲不存在！请重新查找...";
			Sleep(750);
			Draw::gotoxy(32, 15);
			cout << "                           ";
		}
		else {    //歌曲存在
			int count = 1;//第几页
			int sum = (findSong.size() + 4) / 5;  //共几页

			Draw::gotoxy(28, 17);
			cout << "第 " << count << " 页，共 " << sum << " 页";
			Draw::gotoxy(28, 18);
			cout << "上一页↑，下一页↓，esc结束";

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
			Draw::gotoxy(28, 11);
			cout << "相关歌曲如下：";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			Draw::gotoxy(28, 19);
			cout << "请选择要添加的歌曲在当前页序号";

			while (1) {
				for (unsigned int i = 0; i < 5; ++i)
				{
					Draw::gotoxy(28, 12 + i);
					cout << "                                      ";
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
				Draw::gotoxy(31, 17);
				cout << count;
				unsigned int n = (count - 1) * 5;
				for (unsigned int i = 0; i < 5 && i + n < findSong.size(); ++i)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
					Draw::gotoxy(30, 12 + i);
					cout << i + 1;
					Draw::gotoxy(43, 12 + i);
					cout << findSong[i + n].songName;
					Draw::gotoxy(60, 12 + i);
					cout << findSong[i + n].singerName;
				}
				int flag = getInput();
				if (flag == 0) {
					for (unsigned int i = 0; i < 9; ++i)
					{
						Draw::gotoxy(28, 11 + i);
						cout << "                                      ";
					}
					break;
				}
				else if (flag == 1)
				{
					if (count > 1)count--;
				}
				else if (flag == 2)
				{
					if (count < sum)count++;
				}
				else if (flag > 2 && flag < 8)
				{
					flag = flag - 3;
					if (mySong.empty())  //歌单中尚无歌曲
					{
						PlayMusic play;
						PlayMusic *const this1 = &play;
						findSong[flag + 5 * (count - 1)].status = 0;
						nowTheSong = findSong[flag + 5 * (count - 1)].singerName + "-" + findSong[flag + 5 * (count - 1)].songName;
						play.th1 = thread(&PlayMusic::playMusic, this1);
						play.th2 = thread(&PlayMusic::printLyrics, this1);
						play.th1.detach();
						play.th2.detach();
					}
					mySong.push_back(findSong[flag + 5 * (count - 1)]);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
					Draw::gotoxy(36, 20);
					cout << "添加成功！！！";
					Sleep(750);
					Draw::gotoxy(36, 20);
					cout << "                          ";
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
					Draw::gotoxy(36, 20);
					cout << "歌曲不存在！请重新选择...";
					Sleep(750);
					Draw::gotoxy(36, 20);
					cout << "                          ";
				}
			}
		}
	}
}