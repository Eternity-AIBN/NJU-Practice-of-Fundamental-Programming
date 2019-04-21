#include"User.h"

int judgeWho(string s) //根据用户名判断是哪个用户
{
	if (s == "user1")
		return 0;
	if (s == "user2")
		return 1;
	if (s == "user3")
		return 2;
	if (s == "user4")
		return 3;
	if (s == "user5")
		return 4;
	if (s == "user6")
		return 5;
	if (s == "user7")
		return 6;
	if (s == "user8")
		return 7;
	return -1;
}

int judgePer(string s) //根据权限名判断是哪个权限
{
	if (s == "DROP")
		return 0;
	if (s == "INSERT")
		return 1;
	if (s == "DELECT")
		return 2;
	if (s == "SELECT")
		return 3;
	return -1;
}

void User::grant()
{
	vector<string> perList; //授权权限列表
	string tmpName;    //表名
	unsigned int i = 1;
	for (; ParseStatement::result[i] != "on"; ++i);
	++i;
	tmpName = ParseStatement::result[i];

	unsigned int aa = 0;//在allThePermission找到相应表格
	for (; aa < allThePermission.size(); ++aa)
		if (allThePermission[aa].tableName == tmpName)break;
	vector<string> userList; //授权用户列表
	for (i = 1; ParseStatement::result[i] != "on"; ++i)
		if (judge(tmpName, ParseStatement::result[i]))  //拥有该权限才可授权
			perList.push_back(ParseStatement::result[i]);
	if (perList.size() == 0)
		return;
	if (ParseStatement::result.back() == "public") //给所有用户授权
	{
		userList.push_back("user1");
		userList.push_back("user2");
		userList.push_back("user3");
		userList.push_back("user4");
		userList.push_back("user5");
		userList.push_back("user6");
		userList.push_back("user7");
		userList.push_back("user8");
	}
	else for (i += 3; i < ParseStatement::result.size(); ++i)
		userList.push_back(ParseStatement::result[i]);
	for (auto it = userList.begin(); it != userList.end(); ) //防止自身授权
		if (*it == user[n].getInfo().userName)
			it = userList.erase(it);
		else it++;

	for (unsigned int j = 0; j < userList.size(); ++j)  //更新pofUser
	{
		int nn = judgeWho(userList[j]);
		if (nn == -1)continue; //没有该用户

		if (user[nn].pofUser.size() == 0) //尚且没有表格权限
		{
			permissionOfAUser pp;
			pp.tableName = tmpName;
			pp.isOwner = false;
			for (auto it = perList.begin(); it != perList.end(); ++it)
				pp.perm.push_back(*it);
			user[nn].pofUser.push_back(pp);
		}
		else {
			unsigned int h = 0;
			for (; h < user[nn].pofUser.size(); ++h)
				if (user[nn].pofUser[h].tableName == tmpName)
					break;
			if (h == user[nn].pofUser.size())  //尚且没有该表格权限
			{
				permissionOfAUser pp;
				pp.tableName = tmpName;
				pp.isOwner = false;
				for (auto it = perList.begin(); it != perList.end(); ++it)
					pp.perm.push_back(*it);
				user[nn].pofUser.push_back(pp);
			}
			else {
				for (unsigned int k = 0; k < perList.size(); ++k)
				{
					vector<string>::iterator itt = find(user[nn].pofUser[h].perm.begin(), user[nn].pofUser[h].perm.end(), perList[k]);
					if (itt == user[nn].pofUser[h].perm.end())  //未拥有该权限
						user[nn].pofUser[h].perm.push_back(perList[k]);
				}
			}
		}
	}

	for (unsigned int j = 0; j < perList.size(); ++j)  //更新allThePermission
	{
		int nn = judgePer(perList[j]);
		for (unsigned int h = 0; h < userList.size(); ++h)
			allThePermission[aa].permissionList[nn].permissionTree.insertAfter(user[n].getInfo().userName, userList[h]);
	}
}