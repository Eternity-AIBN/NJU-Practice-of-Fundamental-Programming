#include"ParseStatement.h"
#include"User.h"
#include"Table.h"
#include<iostream>
#include<string>
using namespace std;

User user[8];
vector<Table> tables;  //所有表格
int User::n;
vector<Permission> allThePermission;  //所有表格的权限

void init()
{
	UserInfo info[8];
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 4; ++j)
			info[i].permission[j] = false;
	}
	ifstream fin("user.txt");
	fin >> info[0].userName >> info[0].password;
	for (int i = 0; fin.eof()==0; ++i)
	{
		fin >> info[i].userName >> info[i].password;
		user[i] = info[i];
	}
	fin.close();
}

void cat(string filename)
{
	fstream fin(filename);
	if (!fin.is_open())
	{
		cout << "Open File Error!" << endl;
		return;
	}
	string tmp;
	while (!fin.eof())
	{
		getline(fin, tmp);
		cout << tmp << endl;
	}
}

int main()
{
	init();
	string s, s1;

	while (1)
	{
		cout << "~$ ";
		cin >> s1;
		if (s1 == "mySQL")  //进入mySQL程序
		{
			int n = User::login();
			if (n == -1)
				cout << "Login unsuccessfully" << endl;
			else {
				User::n = n;
				user[n].run();
			}
		}
		else if (s1 == "cat")  //查看文件
		{
			string filename;
			cin >> filename;
			cat(filename);
			cin.get();
		}
	}

	return 0;
}