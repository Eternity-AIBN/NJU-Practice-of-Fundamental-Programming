#define _SCL_SECURE_NO_WARNINGS
#include"PlayMusic.h"
#include<fstream>

void PlayMusic::playMusic()
{
	while (1) {
		string tmp = "open " + nowTheSong + ".mp3 alias song";
		LPCSTR lpc = tmp.c_str();
		mciSendStringA(lpc, NULL, 0, NULL);   //��MP3�ļ�
		mciSendString(TEXT("play song repeat"), NULL, 0, NULL);   //���Ÿ���
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
		for (; i < time.size() - 1; ++i)  //��ӡ���
		{
			if (cutSongFlag2 == true) //�и�
			{
				Draw::gotoxy(30, 26);
				cout << "                                   ";
				input.close();
				cutSongFlag2 = false;
				break;
			}
			if (backToMain == true)  //�ص������棬�߳̽���
			{
				Draw::gotoxy(30, 26);
				cout << "                                   ";
				input.close();
				backToMain = false;
				return;
			}
			lyrics[i + 4].assign(lyrics[i + 4], 10, lyrics[i + 4].size() - 10);
			Draw::gotoxy(30, 26);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
			cout << lyrics[i + 4] << endl;
			lastTime = (int)((time[i + 1] - time[i]) * 1000);
			Sleep(lastTime);
			Draw::gotoxy(30, 26);
			cout << "                                   ";
		}
		if (i == time.size() - 1)   //��ӡ���һ����
		{
			Draw::gotoxy(30, 26);
			lyrics[i + 4].assign(lyrics[i + 4], 10, lyrics[i + 4].size() - 10);
			cout << lyrics[i + 4];
		}
	}
}