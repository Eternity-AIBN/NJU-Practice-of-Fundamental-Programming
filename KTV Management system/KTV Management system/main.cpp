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

vector<Song> songs;

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
	InfoHandle::deleteSong();

	/*while (1)
	{
		MainInterface::printMain();
		int choice1 = MainInterface::mainChoice();
		if (choice1 == 0)
		{
			MainInterface::printLogin();
			if (idAndPassword.judge())
				while (1)
				{
					AdminInterface::printAdmin();
					int choice2 = AdminInterface::adminChoice();
					switch (choice2)
					{
					case 0:InfoHandle::songInquire();break;
					case 1:InfoHandle::addSong();break;
					case 2:InfoHandle::bulkImport();break;
					case 3:InfoHandle::deleteSong();break;
					case 4:
					case 5:
					case 6: {
						idAndPassword.printChange();
						idAndPassword.changePassword();
						break;
					}
					case 7:break;
					}
					if (choice2 == 7)break;
				}
			else break;
		}
		else if (choice1 == 1)
		{
			UserInterface::printUser();
			int choice3 = UserInterface::userChoice();
		}
		else if (choice1 == 2)return 0;
	}*/
	return 0;
}

