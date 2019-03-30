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
	static void songInquire();  //歌曲信息查询
	static void addSong();   //增加歌曲
	static void bulkImport();  //批量导入歌曲
	static void deleteSong();  //删除歌曲
	static void modifyInfo();  //修改歌曲信息
	static void songRanking(); //歌曲排行

	static void choiceSinger(); //歌手点歌
	static void choiceSong();  //歌名点歌
	static void choicePhoneticize();  //拼音点歌
	static void haveSelected();  //查看已点歌曲
	static void cutSong();   //切歌

	static bool judgeExist(const Song &tmp);  //判断歌单中是否存在tmp
	static int getInput();  //判断输入的按键

};