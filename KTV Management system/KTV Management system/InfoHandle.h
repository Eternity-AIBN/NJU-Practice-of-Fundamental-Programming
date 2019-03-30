#pragma once
#include"Songs.h"
#include"Draw.h"
#include<iostream>
#include<conio.h>
using namespace std;

extern vector<Song> songs;

class InfoHandle
{
	vector<Song> mySong;

public:
	static void songInquire();  //������Ϣ��ѯ
	static void addSong();   //���Ӹ���
	static void bulkImport();  //�����������
	static void deleteSong();  //ɾ������
	static void modifyInfo();  //�޸ĸ�����Ϣ
	static void songRanking(); //��������

	static void choiceSinger(); //���ֵ��
	static void choiceSong();  //�������
	static void choicePhoneticize();  //ƴ�����
	static void haveSelected();  //�鿴�ѵ����
	static void cutSong();   //�и�

	static bool judgeExist(const Song &tmp);  //�жϸ赥���Ƿ����tmp
	static int getInput();  //�ж�����İ���

};