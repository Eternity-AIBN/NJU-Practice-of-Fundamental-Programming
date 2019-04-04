#pragma once
#include"Draw.h"
#include<string>
using namespace std;

extern string nowTheSong;
extern bool cutSongFlag; 

class UserInterface
{
public:
	static void printUser();  //显示用户界面
	static int userChoice();  //选择功能
	static void run();        //运行

};

