#include"User.h"

void User::recordPermission(string tmpName)
{
	for (int i = 0; i < 4; ++i)          //owner拥有所有权限
		user[n].getInfo().permission[i] = true;
	permissionOfAUser poau;
	poau.tableName = tmpName;
	poau.isOwner = true;    //表格创建者是owner
	poau.perm.push_back("DROP");
	poau.perm.push_back("INSERT");
	poau.perm.push_back("DELETE");
	poau.perm.push_back("SELECT");
	user[n].pofUser.push_back(poau);

	Permission tmp;
	tmp.tableName = tmpName;
	tmp.owner = user[n].getInfo().userName;
	tmp.permissionList[0].permissionName = "DROP";
	tmp.permissionList[1].permissionName = "INSERT";
	tmp.permissionList[2].permissionName = "DELETE";
	tmp.permissionList[3].permissionName = "SELECT";
	for (int i = 0; i < 4; ++i)
		tmp.permissionList[i].permissionTree.setUser(tmp.owner);

	allThePermission.push_back(tmp);
}

bool User::createTable()
{
	if (ParseStatement::result.size() < 5)   //指令无效
	{
		cout << "Invalid instruction!" << endl;
		return false;
	}
	string tmpName = ParseStatement::result[2];  //表的名字
	for (unsigned int i = 0; i < tables.size(); ++i)
		if (tmpName == tables[i].tableName)      //表格已经存在
		{
			cout << "The table has already exist!" << endl;
			return false;
		}
	if (ParseStatement::result[3] == "FROM")
	{
		const char *filename = ParseStatement::result[4].c_str();
		ifstream fin(filename);
		if (!fin.is_open())   //文件不存在
		{
			cout << "The file is not exist!" << endl;
			return false;
		}
		char c;
		Table tmp;
		tmp.tableName = tmpName;

		recordPermission(tmpName);

		string theAttribute, dt;
		getline(fin, theAttribute);
		string temp;
		for (unsigned int k = 0; k< theAttribute.size(); ++k)
		{
			if (theAttribute[k] == '\t')
			{
				tmp.attribute.push_back(temp);
				temp.clear();
			}
			else temp += theAttribute[k];
		}
		tmp.attribute.push_back(temp);
		while (!fin.eof())
		{
			string t;
			Data LineOfData;
			fin >> LineOfData.id;
			fin >> c;
			getline(fin, t);
			string temp;
			for (unsigned int k = 0; k< t.size(); ++k)
			{
				if (t[k] == '\t')
				{
					LineOfData.data.push_back(temp);
					temp.clear();
				}
				else temp += t[k];
			}
			LineOfData.data.push_back(temp);
			tmp.datas.push_back(LineOfData);
		}
		tables.push_back(tmp);
		fin.close();
		return true;

	}
	else {
		Table tmp;
		string theAttribute;
		tmp.tableName = tmpName;
		unsigned int i = 0;
		theAttribute = "ID";
		tmp.attribute.push_back(theAttribute);
		for (; i < ParseStatement::result.size() - 5; ++i)
		{
			theAttribute = ParseStatement::result[i + 3];
			tmp.attribute.push_back(theAttribute);
		}
		tables.push_back(tmp);
		ofstream fout(ParseStatement::result[i + 4]);
		if (fout) {          // 创建成功
			unsigned int j = 0;
			for (; j < tmp.attribute.size() - 1; ++j)
				fout << tmp.attribute[j] << '\t';
			fout << tmp.attribute[j] << endl;
			fout.close();

			recordPermission(tmpName);

			return true;
		}
		return false;
	}
}