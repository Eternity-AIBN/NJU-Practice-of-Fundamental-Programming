#include<iostream>
using namespace std;
#include"Draw.h"
#include"MainInterface.h"
#include"AdminInterface.h"
#include"UserInterface.h"
#include"IdAndPassword.h"
#include"Songs.h"
#include"InfoHandle.h"
#include<vector>
#include<fstream>

vector<Song> songs, mySong;
IdAndPassword idAndPassword;

void init()  //初始化歌单
{
	ifstream fin("in.txt");
	if (!fin.is_open())   //文件打开失败
	{
		cerr << "Error" << endl;
		exit(-1);
	}
	Song tmp;
	string str;
	int n;
	bool m;
	float a;
	while (fin >> n)
	{
		tmp.id = n;
		fin >> str;
		tmp.songName = str;
		fin >> str;
		tmp.singerName = str;
		fin >> str;
		tmp.songAbbreviation = str;
		fin >> m;
		tmp.status = m;
		fin >> a;
		tmp.score = a;
		songs.push_back(tmp);
	}
	fin.close();
}

int main()
{
	ios::sync_with_stdio(false);

	IdAndPassword idAndPassword;
	system("mode 100,30");

	init();

	while (1)
	{
		MainInterface::printMain();
		int choice = MainInterface::mainChoice();
		if (choice == 0)
			AdminInterface::run();
		else if (choice == 1)
			UserInterface::run();
		else if (choice == 2)return 0;
	}

}

