#include"InfoHandle.h"

void InfoHandle::judgeSongPhoneticize(vector<Song> &findSong, const string &s)
{
	findSong.clear();
	for (auto song2 : songs)
		if (song2.songAbbreviation == s)
			findSong.push_back(song2);
}

void InfoHandle::choosePhoneticize()
{
	system("cls");
	string name;
	vector<Song> findSong;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	Draw::drawRect(26, 7, 45, 12);
	Draw::gotoxy(40, 8);
	cout << "***ƴ�����***";
	Draw::gotoxy(28, 10);
	cout << "����Ҫ���ҵĸ���ƴ��(end����)��";
	while (1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
		Draw::gotoxy(59, 10);
		cout << "        ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		Draw::gotoxy(59, 10);
		cin >> name;
		if (name == "end")return;
		judgeSongPhoneticize(findSong, name);
		if (findSong.size() == 0)  //����������
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			Draw::gotoxy(32, 15);
			cout << "�ø��������ڣ������²���...";
			Sleep(750);
			Draw::gotoxy(32, 15);
			cout << "                           ";
		}
		else {    //��������
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
			Draw::gotoxy(28, 11);
			cout << "��ظ������£�";
			unsigned int i = 0;
			for (; i < findSong.size(); ++i)
			{
				Draw::gotoxy(30, 12 + i);
				cout << findSong[i].id;
				Draw::gotoxy(35, 12 + i);
				cout << findSong[i].songName;
				Draw::gotoxy(55, 12 + i);
				cout << findSong[i].singerName;
			}
			while (1) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
				Draw::gotoxy(28, 12 + i);
				cout << "��ѡ����Ҫ��ӵĸ���ID(����0����)��   \b\b\b";
				int num;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
				cin >> num;
				if (num == 0)break;
				else {
					int locate = judgeID(findSong, num);
					if (locate != -1)
					{
						if (mySong.empty())
							findSong[locate].status = 0;
						mySong.push_back(findSong[locate]);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
						Draw::gotoxy(36, 14 + i);
						cout << "��ӳɹ�������";
					}
					else {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
						Draw::gotoxy(36, 14 + i);
						cout << "���������ڣ�������ѡ��...";
					}
					Sleep(750);
					Draw::gotoxy(36, 14 + i);
					cout << "                          ";
				}
			}
			for (i = 0; i <= findSong.size() + 1; ++i)
			{
				Draw::gotoxy(28, 11 + i);
				cout << "                                      ";
			}
		}
	}
}