#include"User.h"

void User::deleteFrom()
{
	if (ParseStatement::result.size() < 4)   //ָ����Ч
	{
		cout << "Invalid instruction!" << endl;
		return;
	}
	if (ParseStatement::result[1] == "FROM"&&ParseStatement::result[3]=="WHERE") //ɾ��ĳһ��
	{
		string tmp = ParseStatement::result[2];  //����

		if (!judge(tmp, "DELETE"))
		{
			cout << "(mysql)==> Permission denied!" << endl;
			return;
		}

		auto it = tables.begin();
		for (; it != tables.end(); ++it)
			if (it->tableName == tmp)    //�ҵ���Ӧ���
				break;
		if (it == tables.end())
		{
			cout << "The table is not exist!";
			return;
		}
		string column = ParseStatement::result[4];
		string value = ParseStatement::result[6];

		unsigned int i = 1;        //column��Ӧ��i+1������
		for (; i < it->attribute.size(); ++i)
			if (it->attribute[i] == column)break;
		if (i == it->attribute.size()) {  //���Բ�����
			cout << "The attribute is not exist!" << endl;
			return;
		}
		
		bool flag = false;
		auto &pdata = it->datas.begin();   // �ӱ���ɾ��
		for (; pdata != it->datas.end(); ++pdata)
			if (pdata->data[i - 1] == value)
			{
				pdata = it->datas.erase(pdata);
				flag = true;
				break;
			}
		if (!flag)
		{
			cout << "The value is not exist!" << endl;
			return;
		}
		else {  
			for (; pdata != it->datas.end(); ++pdata)
				pdata->id--;
			
			//ͬ������ļ�
			string fname = tmp + ".txt";
			const char *filename = fname.c_str();
			int n = remove(filename);    
			ofstream fout(filename);

			if (fout) {          // �����ɹ�
				unsigned int j = 0;
				for (; j < it->attribute.size()-1; ++j)
					fout << it->attribute[j] << '\t';
				fout << it->attribute[j] << endl;
				for (unsigned int i = 0; i < it->datas.size(); ++i)
				{
					unsigned int k = 0;
					fout << it->datas[i].id << '\t';
					for (; k < it->datas[i].data.size() - 1; ++k)
						fout << it->datas[i].data[k] << '\t';
					fout << it->datas[i].data[k] << endl;
				}
				fout.close();
			}
		}
	}
	else {
		string tmp = ParseStatement::result[3];  //����

		if (!judge(tmp, "DELETE"))
		{
			cout << "(mysql)==> Permission denied!" << endl;
			return;
		}

		auto it = tables.begin();
		for (; it != tables.end(); ++it)
			if (it->tableName == tmp)    //�ҵ���Ӧ���
				break;

		it->datas.erase(it->datas.begin(), it->datas.end());  //�ӱ���ɾ��

		string fname = tmp + ".txt";   //ͬ����Ӧ�ļ�
		const char *filename = fname.c_str();
		int n = remove(filename);
		ofstream fout(filename);

		if (fout) {          // �����ɹ�
			unsigned int j = 0;
			for (; j < it->attribute.size() - 1; ++j)
				fout << it->attribute[j] << '\t';
			fout << it->attribute[j] << endl;
		}
		fout.close();
		return;
	}
}