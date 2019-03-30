#pragma once
#include<string>
#include<vector>

struct Song
{
	int id;   //歌曲ID(编号)
	int serialNum;  //播放列表歌曲序号
	std::string songName;  //歌曲名
	std::string singerName;  //歌手名
	std::string songAbbreviation;  //歌曲名缩写
	bool status;   //歌曲状态(0表示正在播放，1表示未播放)
	float score;   //用户评分
};