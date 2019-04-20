#include"User.h"
#include<cstdio>

void User::dropTable()
{
	if (ParseStatement::result.size() !=3)   //指令无效
	{
		cout << "Invalid instruction!" << endl;
		return;
	}
	string tmp = ParseStatement::result[2];  //表的名字

	for (auto it = user[n].pofUser.begin(); it != user[n].pofUser.end(); ++it)
		if (it->tableName == tmp)        //从用户的权限列表中删除该表格
		{
			it = user[n].pofUser.erase(it);
			break;
		}

	for (auto it = tables.begin(); it != tables.end(); ++it)
		if (it->tableName == tmp)    //从所有表格中删除该表格
		{
			it = tables.erase(it);
			tmp = tmp + ".txt";
			const char *filename = tmp.c_str();
			int n = remove(filename);
			return;
		}
}