#include"User.h"
#include<cstdio>

void User::dropTable()
{
	if (ParseStatement::result.size() !=3)   //ָ����Ч
	{
		cout << "Invalid instruction!" << endl;
		return;
	}
	string tmp = ParseStatement::result[2];  //�������

	for (auto it = user[n].pofUser.begin(); it != user[n].pofUser.end(); ++it)
		if (it->tableName == tmp)        //���û���Ȩ���б���ɾ���ñ��
		{
			it = user[n].pofUser.erase(it);
			break;
		}

	for (auto it = tables.begin(); it != tables.end(); ++it)
		if (it->tableName == tmp)    //�����б����ɾ���ñ��
		{
			it = tables.erase(it);
			tmp = tmp + ".txt";
			const char *filename = tmp.c_str();
			int n = remove(filename);
			return;
		}
}