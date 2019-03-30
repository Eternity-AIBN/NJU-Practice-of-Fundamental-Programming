#pragma once
#include"Songs.h"
#include"Draw.h"
#include<iostream>
#include<conio.h>
using namespace std;

extern vector<Song> songs;
extern vector<Song> mySong;  

class InfoHandle
{
public:
	static void songInquire();  //������Ϣ��ѯ
	static void addSong();   //���Ӹ���
	static void bulkImport();  //�����������
	static void deleteSong();  //ɾ������
	static void modifyInfo();  //�޸ĸ�����Ϣ
	static void songRanking(); //��������

	static void chooseSinger(); //���ֵ��
	static void chooseSongName();  //�������
	static void choosePhoneticize();  //ƴ�����
	static void haveSelected();  //�鿴�ѵ����
	static void cutSong();   //�и�

	static bool judgeExist(const Song &tmp);  //�жϸ赥���Ƿ����tmp
	static int getInput();  //�ж�����İ���

	//���赥�д��ڵ�Ҫ��ĸ��������ѵ�赥
	static void judgeSinger(vector<Song> &findSong, const string &s);
	static void judgeSongName(vector<Song> &findSong, const string &s);
	static void judgeSongPhoneticize(vector<Song> &findSong, const string &s);

	static int judgeID(vector<Song> &findSong, int num);  //�ж������ID���Ƿ��ڴ�ѡ������,�������ڴ�ѡ���������
	
};