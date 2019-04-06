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
	thread th1;    //创建一个子线程用于播放音乐
	thread th2;    //创建另一个子线程用于打印歌词

	void playMusic();   //播放音乐
	void printLyrics();   //打印歌词 
};