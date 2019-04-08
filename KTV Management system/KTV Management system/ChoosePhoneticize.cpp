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
	cout << "***ƴ�����***";
	Draw::gotoxy(28, 10);
	cout << "����Ҫ���ҵ�ƴ��(end����)��";
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
			int count = 1;//�ڼ�ҳ
			int sum = (findSong.size() + 4) / 5;  //����ҳ

			Draw::gotoxy(28, 17);
			cout << "�� " << count << " ҳ���� " << sum << " ҳ";
			Draw::gotoxy(28, 18);
			cout << "��һҳ������һҳ����esc����";

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
			Draw::gotoxy(28, 11);
			cout << "��ظ������£�";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			Draw::gotoxy(28, 19);
			cout << "��ѡ��Ҫ��ӵĸ����ڵ�ǰҳ���";

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
					if (mySong.empty())  //�赥�����޸���
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
					cout << "��ӳɹ�������";
					Sleep(750);
					Draw::gotoxy(36, 20);
					cout << "                          ";
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
					Draw::gotoxy(36, 20);
					cout << "���������ڣ�������ѡ��...";
					Sleep(750);
					Draw::gotoxy(36, 20);
					cout << "                          ";
				}
			}
		}
	}
}