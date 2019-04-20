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
	UserInfo info[4];
	info[0].userName = "user1";
	info[1].userName = "user2";
	info[2].userName = "user3";
	info[3].userName = "user4";

	info[0].password = "user111";
	info[1].password = "user222";
	info[2].password = "user333";
	info[3].password = "user444";

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			info[i].permission[j] = false;
	}

	user[0] = info[0];
	user[1] = info[1];
	user[2] = info[2];
	user[3] = info[3];
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
	/*cout << "~$ ";
	cin >> s1;
	if (s1 != "mySQL")
		return 0;

	int n = User::login();
	if (n == -1)
		cout << "Login unsuccessfully" << endl;
	else {
		cout << "Login successfully" << endl;
		User::n = n;
		user[n].run();
	}*/
	while (1)
	{
		user[0].run();
		cout << "~$ cat ";
		string fil;
		cin >> fil;
		cat(fil);
		cin.get();
	}
	

	/*user[0].run();
	for (int i = 0; i < 3; ++i)
		cout << tables[0].attribute[i] << " ";
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 3; ++j)
			cout << tables[0].datas[i].data[j] << " ";
	cout << endl;*/

	/*while (1)
	{
		User::run();
	}*/
}