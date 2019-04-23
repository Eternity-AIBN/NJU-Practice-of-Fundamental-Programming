#include"User.h"

extern int judgeWho(string s);
extern int judgePer(string s);

void User::revoke()
{
	vector<string> perList; //�ջ�Ȩ���б�
	string tmpName;    //����
	unsigned int i = 1;
	for (; ParseStatement::result[i] != "on"; ++i);
	++i;
	tmpName = ParseStatement::result[i];
	vector<string> userList; //�û��б�
	for (i += 2; i < ParseStatement::result.size(); ++i)
		if (ParseStatement::result[i] != user[n].getInfo().userName)  //��ֹ�Լ��ջ��Լ���Ȩ��
			userList.push_back(ParseStatement::result[i]);

	unsigned int aa = 0;//��allThePermission�ҵ���Ӧ���
	for (; aa < allThePermission.size(); ++aa)
		if (allThePermission[aa].tableName == tmpName)break;

	if (ParseStatement::result[1] == "all")
	{
		if (judge(tmpName, "DROP"))
			perList.push_back("DROP");
		if (judge(tmpName, "INSERT"))
			perList.push_back("INSERT");
		if (judge(tmpName, "DELETE"))
			perList.push_back("DELETE");
		if (judge(tmpName, "SELECT"))
			perList.push_back("SELECT");
	}
	else for (i = 1; ParseStatement::result[i] != "on"; ++i)
		if (judge(tmpName, ParseStatement::result[i]))  //ӵ�и�Ȩ�޲ſ���Ȩ
			perList.push_back(ParseStatement::result[i]);
	if (perList.size() == 0)
		return;

	vector<string> allUserList;

	for (unsigned int j = 0; j < perList.size(); ++j)
	{
		int nn = judgePer(perList[j]);
		for (unsigned int h = 0; h < userList.size(); ++h)
		{
			TNode *tmpp = allThePermission[aa].permissionList[nn].permissionTree.bfs2(allThePermission[aa].permissionList[nn].permissionTree.father, userList[h]);
			Tree::treeRevoke(tmpp, allUserList);
		}
	}
	cout << allUserList.size() << endl;
	for (unsigned int j = 0; j < allUserList.size(); ++j)  //����pofUser
	{
		int nn = judgeWho(allUserList[j]);
		if (nn == -1)continue; //û�и��û�

		if (user[nn].pofUser.size() == 0)
			return;

		unsigned int h = 0;
		for (; h < user[nn].pofUser.size(); ++h)
			if (user[nn].pofUser[h].tableName == tmpName)
				break;
		if (h == user[nn].pofUser.size())  
			return;
		else for (unsigned int k = 0; k < perList.size(); ++k)
				for (auto it = user[nn].pofUser[h].perm.begin(); it != user[nn].pofUser[h].perm.end(); ++it)
					if (*it == perList[k])
					{
						user[nn].pofUser[h].perm.erase(it);
						break;
					}
	}


	for (unsigned int j = 0; j < perList.size(); ++j)  //����allThePermission
	{
		int nn = judgePer(perList[j]);
		for (unsigned int h = 0; h < userList.size(); ++h)
			allThePermission[aa].permissionList[nn].permissionTree.deleteNode(user[n].getInfo().userName, userList[h]);
	}

}
