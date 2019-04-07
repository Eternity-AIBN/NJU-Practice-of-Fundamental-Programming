#pragma once
#include"Songs.h"
#include"Draw.h"
#include"PlayMusic.h"
#include<iostream>
#include<string>
using namespace std;

extern vector<Song> songs;
extern vector<Song> mySong; 
extern string nowTheSong;

class InfoHandle
{
public:
	static void songInquire();  //歌曲信息查询
	static void addSong();   //增加歌曲
	static void bulkImport();  //批量导入歌曲
	static void deleteSong();  //删除歌曲
	static void modifyInfo();  //修改歌曲信息
	static void songRanking(); //歌曲排行

	void chooseSinger(); //歌手点歌
	void chooseSongName();  //歌名点歌
	void choosePhoneticize();  //拼音点歌
	static void haveSelected();  //查看已点歌曲

	static bool judgeExist(const Song &tmp);  //判断歌单中是否存在tmp
	static int getInput();  //判断输入的按键

	//将歌单中存在的要点的歌曲加入已点歌单
	static void judgeSinger(vector<Song> &findSong, const string &s);
	static void judgeSongName(vector<Song> &findSong, const string &s);
	static void judgeSongPhoneticize(vector<Song> &findSong, const string &s);

	static int judgeID(vector<Song> &findSong, int num);  //判断输入的ID号是否在待选歌曲中,返回其在待选歌曲中序号
	
};