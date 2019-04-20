#include"User.h"

bool User::createTable()
{
	if (ParseStatement::result.size() < 5)   //ָ����Ч
	{
		cout << "Invalid instruction!" << endl;
		return false;
	}
	string tmpName = ParseStatement::result[2];  //�������
	for (unsigned int i = 0; i < tables.size(); ++i)
		if (tmpName == tables[i].tableName)      //����Ѿ�����
		{
			cout << "The table has already exist!" << endl;
			return false;
		}
	if (ParseStatement::result[3] == "FROM")
	{
		const char *filename = ParseStatement::result[4].c_str();
		ifstream fin(filename);
		if (!fin.is_open())   //�ļ�������
		{
			cout << "The file is not exist!" << endl;
			return false;
		}
		char c;
		Table tmp;
		tmp.tableName = tmpName;

		for (int i = 0; i < 4; ++i)          //ownerӵ������Ȩ��
			user[n].getInfo().permission[i] = true;
		permissionOfAUser poau;
		poau.tableName = tmpName;
		poau.isOwner = true;    //��񴴽�����owner
		poau.perm.push_back("DROP");
		poau.perm.push_back("INSERT");
		poau.perm.push_back("DELETE");
		poau.perm.push_back("SELECT");
		user[n].pofUser.push_back(poau);

		string id;
		fin >> id;
		string theAttribute, dt;
		while ((c = fin.get()) != '\n')
		{
			fin >> theAttribute;
			tmp.attribute.push_back(theAttribute);
		}
		while (fin.peek()!=EOF)
		{
			Data LineOfData;
			fin >> id;
			while ((c = fin.get()) != '\n')
			{
				fin >> dt;
				LineOfData.data.push_back(dt);
			}
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
		for (; i < ParseStatement::result.size() - 5; ++i)
		{
			theAttribute = ParseStatement::result[i + 3];
			tmp.attribute.push_back(theAttribute);
		}
		tables.push_back(tmp);
		ofstream fout(ParseStatement::result[i + 4]);
		if (fout) {          // �����ɹ�
			fout << "ID\t";
			unsigned int j = 0;
			for (; j < tmp.attribute.size() - 1; ++j)
				fout << tmp.attribute[j] << '\t';
			fout << tmp.attribute[j] << endl;
			fout.close();

			for (int i = 0; i < 4; ++i)          //ownerӵ������Ȩ��
				user[n].getInfo().permission[i] = true;
			permissionOfAUser poau;
			poau.tableName = tmpName;
			poau.isOwner = true;    //��񴴽�����owner
			poau.perm.push_back("DROP");
			poau.perm.push_back("INSERT");
			poau.perm.push_back("DELETE");
			poau.perm.push_back("SELECT");
			user[n].pofUser.push_back(poau);

			cout << " asdfg" << endl;
			return true;
		}
		return false;
	}
}