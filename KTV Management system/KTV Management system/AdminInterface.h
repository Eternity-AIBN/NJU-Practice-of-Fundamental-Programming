#pragma once
#include"Draw.h"
#include<string>

extern bool switchAdmin;

class AdminInterface
{
public:
	static void printAdmin();  //��ʾ����Ա����
	static int adminChoice();  //ѡ����
	static void run();         //����

};
