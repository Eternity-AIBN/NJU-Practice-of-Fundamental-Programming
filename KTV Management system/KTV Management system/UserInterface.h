#pragma once
#include"Draw.h"
#include<string>
using namespace std;

extern string nowTheSong;
extern bool cutSongFlag; 

class UserInterface
{
public:
	static void printUser();  //��ʾ�û�����
	static int userChoice();  //ѡ����
	static void run();        //����

};

