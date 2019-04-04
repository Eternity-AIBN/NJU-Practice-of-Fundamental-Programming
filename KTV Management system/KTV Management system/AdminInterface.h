#pragma once
#include"Draw.h"
#include<string>

extern bool switchAdmin;

class AdminInterface
{
public:
	static void printAdmin();  //显示管理员界面
	static int adminChoice();  //选择功能
	static void run();         //运行

};
