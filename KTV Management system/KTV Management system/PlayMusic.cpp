#define _SCL_SECURE_NO_WARNINGS
#include"PlayMusic.h"
#include<fstream>

void PlayMusic::playMusic()
{
	while (1) {
		string tmp = "open " + nowTheSong + ".mp3 alias song";
		LPCSTR lpc = tmp.c_str();
		mciSendStringA(lpc, NULL, 0, NULL);   //打开MP3文件
		mciSendString(TEXT("play song"), NULL, 0, NULL);   //播放歌曲
		while (1)  //持续播放
		{
			if (cutSongFlag1 == true)   //切歌
			{
				mciSendString(TEXT("close song"), NULL, 0, NULL);   //关闭上一首歌
				cutSongFlag1 = false;
				Sleep(1800);   //与显示歌词的线程保持同步
				break;
			}
			if (backToMain == true)  //回到主界面，线程结束
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
		vector<string> lyrics; //歌词
		string str;
		char s[6];
		fstream input(nowTheSong + ".lrc");
		if (!input.is_open())   //文件打开失败
			return;
		vector<float> time;   //每句歌词时间点
		int minute;
		float second, tmp;
		while (!input.eof())  //读入歌词
		{
			getline(input, str);
			lyrics.push_back(str);
		}
		for (unsigned int i = 4; i < lyrics.size(); ++i)  //处理时间
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
		int lastTime = (int)(time[0] * 1000);   //每句歌词显示的时间
		unsigned int i = 0;
		Sleep(lastTime);
		Sleep(1000);    //打开mp3文件延迟

		string temp;   //打印第一句歌词
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

		for (i = 1; i < time.size() - 2; ++i)  //打印第二句及之后歌词
		{
			string tmp[3];
			if (cutSongFlag2 == true) //切歌
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
			if (backToMain == true)  //回到主界面，线程结束
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
		if (i == time.size() - 2)   //打印最后一句歌词
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