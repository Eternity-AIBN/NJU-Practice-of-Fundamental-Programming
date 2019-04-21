#include"User.h"

void User::deleteFrom()
{
	if (ParseStatement::result.size() < 4)   //指令无效
	{
		cout << "Invalid instruction!" << endl;
		return;
	}
	if (ParseStatement::result[1] == "FROM"&&ParseStatement::result[3]=="WHERE") //删除某一行
	{
		string tmp = ParseStatement::result[2];  //表名

		if (!judge(tmp, "DELETE"))
		{
			cout << "(mysql)==> Permission denied!" << endl;
			return;
		}

		auto it = tables.begin();
		for (; it != tables.end(); ++it)
			if (it->tableName == tmp)    //找到相应表格
				break;
		if (it == tables.end())
		{
			cout << "The table is not exist!";
			return;
		}
		string column = ParseStatement::result[4];
		string value = ParseStatement::result[6];

		unsigned int i = 1;        //column对应第i+1个属性
		for (; i < it->attribute.size(); ++i)
			if (it->attribute[i] == column)break;
		if (i == it->attribute.size()) {  //属性不存在
			cout << "The attribute is not exist!" << endl;
			return;
		}
		
		bool flag = false;
		auto &pdata = it->datas.begin();   // 从表中删除
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
			
			//同步相关文件
			string fname = tmp + ".txt";
			const char *filename = fname.c_str();
			int n = remove(filename);    
			ofstream fout(filename);

			if (fout) {          // 创建成功
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
		string tmp = ParseStatement::result[3];  //表名

		if (!judge(tmp, "DELETE"))
		{
			cout << "(mysql)==> Permission denied!" << endl;
			return;
		}

		auto it = tables.begin();
		for (; it != tables.end(); ++it)
			if (it->tableName == tmp)    //找到相应表格
				break;

		it->datas.erase(it->datas.begin(), it->datas.end());  //从表中删除

		string fname = tmp + ".txt";   //同步相应文件
		const char *filename = fname.c_str();
		int n = remove(filename);
		ofstream fout(filename);

		if (fout) {          // 创建成功
			unsigned int j = 0;
			for (; j < it->attribute.size() - 1; ++j)
				fout << it->attribute[j] << '\t';
			fout << it->attribute[j] << endl;
		}
		fout.close();
		return;
	}
}