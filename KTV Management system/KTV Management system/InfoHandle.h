#pragma once
#include"Songs.h"
#include"Draw.h"
#include<iostream>
#include<conio.h>
#include<string>
#include<thread>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
using namespace std;

extern vector<Song> songs;
extern vector<Song> mySong; 
extern string nowTheSong;
extern bool cutSongFlag;
extern bool switchAdmin;

class InfoHandle
{
	thread th1;    //����һ�����߳����ڲ�������
	thread th2;    //������һ�����߳����ڴ�ӡ���
    void playMusic();   //��������
	void printLyrics();   //��ӡ���

public:
	static void songInquire();  //������Ϣ��ѯ
	static void addSong();   //���Ӹ���
	static void bulkImport();  //�����������
	static void deleteSong();  //ɾ������
	static void modifyInfo();  //�޸ĸ�����Ϣ
	static void songRanking(); //��������

	void chooseSinger(); //���ֵ��
	void chooseSongName();  //�������
	void choosePhoneticize();  //ƴ�����
	static void haveSelected();  //�鿴�ѵ����

	static bool judgeExist(const Song &tmp);  //�жϸ赥���Ƿ����tmp
	static int getInput();  //�ж�����İ���

	//���赥�д��ڵ�Ҫ��ĸ��������ѵ�赥
	static void judgeSinger(vector<Song> &findSong, const string &s);
	static void judgeSongName(vector<Song> &findSong, const string &s);
	static void judgeSongPhoneticize(vector<Song> &findSong, const string &s);

	static int judgeID(vector<Song> &findSong, int num);  //�ж������ID���Ƿ��ڴ�ѡ������,�������ڴ�ѡ���������
	
};