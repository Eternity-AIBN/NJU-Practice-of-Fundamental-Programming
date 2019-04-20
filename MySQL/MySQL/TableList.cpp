#include"User.h"

void User::tableList()
{
	int num = user[n].pofUser.size();
	cout << "    total:" << num << endl;
	for (int i = 0; i < num; ++i)
	{
		string tmp = user[n].pofUser[i].tableName;
		auto it = tables.begin();
		for (; it != tables.end(); ++it)  //找到相应表格
			if (it->tableName == tmp)
				break;
		cout << '\t' << tmp << ": (" << it->attribute.size() - 1 << ',' << it->datas.size() << ") [";
		for (unsigned int j = 1; j < it->attribute.size(); ++j)
			cout << it->attribute[j] << ", ";
		cout << "\b\b] ";
		for (unsigned int j = 0; j < user[n].pofUser[i].perm.size(); ++j)
			cout << user[n].pofUser[i].perm[j] << ", ";
		cout << "\b\b";
		if (user[n].pofUser[i].isOwner)
			cout << " [OWNER]";
		cout << endl;
	}

}