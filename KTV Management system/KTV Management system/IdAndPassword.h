#pragma once
#include"Draw.h"
#include<string>
using namespace std;
class IdAndPassword
{
	string accountNum;
	string passwordNum;
	int times;  //ʣ���������������������֤ʧ���Զ�����

public:
	IdAndPassword();  //�ṩ��ʼ�˺ź�����
	bool judge();
	void changePassword();  //�޸�����
	void printChange();  //��ʾ�޸��������
	void cinPassword(string &s);  //�������룬��ʾ*

};