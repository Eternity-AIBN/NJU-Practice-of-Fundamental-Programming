#define _SCL_SECURE_NO_WARNINGS
#include"PlayMusic.h"
#include<fstream>

void PlayMusic::playMusic()
{
	while (1) {
		string tmp = "open " + nowTheSong + ".mp3 alias song";
		LPCSTR lpc = tmp.c_str();
		mciSendStringA(lpc, NULL, 0, NULL);   //��MP3�ļ�
		mciSendString(TEXT("play song"), NULL, 0, NULL);   //���Ÿ���
		while (1)  //��������
		{
			if (cutSongFlag1 == true)   //�и�
			{
				mciSendString(TEXT("close song"), NULL, 0, NULL);   //�ر���һ�׸�
				cutSongFlag1 = false;
				Sleep(1800);   //����ʾ��ʵ��̱߳���ͬ��
				break;
			}
			if (backToMain == true)  //�ص������棬�߳̽���
			{
				mciSendString(TEXT("close song"), NULL, 0, NULL);
				return;
			}
		}
	}
}

void PlayMusic::printLyrics()
{
	while (1) {
		vector<string> lyrics; //���
		string str;
		char s[6];
		fstream input(nowTheSong + ".lrc");
		if (!input.is_open())   //�ļ���ʧ��
			return;
		vector<float> time;   //ÿ����ʱ���
		int minute;
		float second, tmp;
		while (!input.eof())  //������
		{
			getline(input, str);
			lyrics.push_back(str);
		}
		for (unsigned int i = 4; i < lyrics.size(); ++i)  //����ʱ��
		{
			lyrics[i].copy(s, 2, 1);
			s[2] = '\0';
			minute = atoi(s);
			lyrics[i].copy(s, 5, 4);
			s[5] = '\0';
			second = (float)atof(s);
			tmp = minute * 60 + second;
			time.push_back(tmp);
		}
		int lastTime = (int)(time[0] * 1000);   //ÿ������ʾ��ʱ��
		unsigned int i = 0;
		Sleep(lastTime);
		Sleep(1000);    //��mp3�ļ��ӳ�

		string temp;   //��ӡ��һ����
		temp.assign(lyrics[4], 10, lyrics[4].size() - 10);
		Draw::gotoxy(30, 30);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << temp;
		Draw::gotoxy(30, 31);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		temp.assign(lyrics[5], 10, lyrics[5].size() - 10);
		cout << temp;
		lastTime = (int)((time[1] - time[0]) * 1000);
		Sleep(lastTime);
		for (int k = 0; k < 3; ++k)
		{
			Draw::gotoxy(30, 29 + k);
			cout << "                                   ";
		}

		for (i = 1; i < time.size() - 2; ++i)  //��ӡ�ڶ��估֮����
		{
			string tmp[3];
			if (cutSongFlag2 == true) //�и�
			{
				for (int k = 0; k < 3; ++k)
				{
					Draw::gotoxy(30, 29 + k);
					cout << "                                   ";
				}
				input.close();
				cutSongFlag2 = false;
				break;
			}
			if (backToMain == true)  //�ص������棬�߳̽���
			{
				input.close();
				backToMain = false;
				return;
			}
			tmp[0].assign(lyrics[i + 3], 10, lyrics[i + 3].size() - 10);
			tmp[1].assign(lyrics[i + 4], 10, lyrics[i + 4].size() - 10);
			tmp[2].assign(lyrics[i + 5], 10, lyrics[i + 5].size() - 10);

			Draw::gotoxy(30, 29);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
			cout << tmp[0] << endl;
			Draw::gotoxy(30, 30);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
			cout << tmp[1] << endl;
			Draw::gotoxy(30, 31);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
			cout << tmp[2] << endl;

			lastTime = (int)((time[i + 1] - time[i]) * 1000);
			Draw::gotoxy(55, 10);
			Sleep(lastTime);
			for (int k = 0; k < 3; ++k)
			{
				Draw::gotoxy(30, 29 + k);
				cout << "                                   ";
			}
		}
		if (i == time.size() - 2)   //��ӡ���һ����
		{
			lyrics[i + 4].assign(lyrics[i + 4], 10, lyrics[i + 4].size() - 10);
			Draw::gotoxy(30, 29);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
			cout << lyrics[i + 4] << endl;
			Draw::gotoxy(30, 30);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
			lyrics[i + 5].assign(lyrics[i + 5], 10, lyrics[i + 5].size() - 10);
			cout << lyrics[i + 5];
		}
	}
}