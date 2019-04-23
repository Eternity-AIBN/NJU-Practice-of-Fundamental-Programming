#include"User.h"

void print(ofstream &fout,TNode *node)
{
	if (node == NULL || node->children.size() == 0)   //目标节点不存在
		return;
	for (unsigned int i = 0; i < node->children.size(); ++i)
		fout << node->user << '-' << node->children[i]->user << "  ";
	fout << endl;
	for (vector<TNode*>::iterator it = node->children.begin(); it != node->children.end(); it++)
		print(fout, *it);   
}

void updatePermission()   //更新本地权限表
{
	ofstream fout("permission.txt");
	if (fout) {
		for (unsigned int i = 0; i < allThePermission.size(); ++i)
		{
			fout << allThePermission[i].tableName << endl;
			for (int j = 0; j < 4; ++j)
			{
				fout << allThePermission[i].permissionList[j].permissionName << endl;
				print(fout, allThePermission[i].permissionList[j].permissionTree.father);
			}
			fout << endl;
		}
	}
}

void User::run()
{
	string s;
	cout << "(mysql)==>";
	getline(cin, s);
	while (s != "quit")
	{
		int choice = ParseStatement::parse(s);
		switch (choice)
		{
		case CREATE:user[n].createTable(); break;
		case DROP:user[n].dropTable(); break;
		case INSERT:user[n].insertInto(); break;
		case DELETE:user[n].deleteFrom(); break;
		case TABLELIST:user[n].tableList(); break;
		case SELECT:user[n].selectFrom(); break;
		case GRANT:user[n].grant(); break;
		case REVOKE:user[n].revoke(); break;
		default:
			break;
		}
		cout << "(mysql)==>";
		getline(cin, s);
	}
	updatePermission();
}