#pragma once
#include"Draw.h"
#include<iostream>
#include<string>
#include<vector>
#include<thread>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
using namespace std;

extern string nowTheSong;
extern bool cutSongFlag1;
extern bool cutSongFlag2;
extern bool backToMain;
extern bool backToUser;

class PlayMusic
{
public:
	thread th1;    //����һ�����߳����ڲ�������
	thread th2;    //������һ�����߳����ڴ�ӡ���

	void playMusic();   //��������
	void printLyrics();   //��ӡ��� 
};