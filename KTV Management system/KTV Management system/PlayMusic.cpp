#define _SCL_SECURE_NO_WARNINGS
#include"InfoHandle.h"
#include<fstream>

void InfoHandle::playMusic()
{
	while (1) {
		string tmp = "open " + nowTheSong + ".mp3 alias song";
		LPCSTR lpc = tmp.c_str();
		mciSendStringA(lpc, NULL, 0, NULL);   //打开MP3文件
		mciSendString(TEXT("play song repeat"), NULL, 0, NULL);   //播放歌曲
		while (1)  //持续播放
			if (cutSongFlag == true)   //切歌
			{
				mciSendString(TEXT("close song"), NULL, 0, NULL);   //关闭上一首歌
				cutSongFlag = false;
				break;
			}
		if (switchAdmin == true)
			return;
	}
}

void InfoHandle::printLyrics()
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
		Sleep(1000);
		for (; i < time.size() - 1; ++i)  //打印歌词
		{
			if (cutSongFlag == true) //切歌
				break;
			lyrics[i + 4].assign(lyrics[i + 4], 10, lyrics[i + 4].size() - 10);
			Draw::gotoxy(30, 22);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
			cout << lyrics[i + 4] << endl;
			lastTime = (int)((time[i + 1] - time[i]) * 1000);
			Sleep(lastTime);
			Draw::gotoxy(30, 22);
			cout << "                                   " << endl;
		}
		if (i == time.size() - 1)   //打印最后一句歌词
		{
			lyrics[i + 4].assign(lyrics[i + 4], 10, lyrics[i + 4].size() - 10);
			cout << lyrics[i + 4] << endl;
		}
	}
}