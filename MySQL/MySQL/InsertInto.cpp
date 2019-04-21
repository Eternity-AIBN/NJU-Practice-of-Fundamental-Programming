#include"User.h"

bool judgeFormat(string t, vector<string> c, vector<string> v)
{
	if (c.size() != v.size())  //属性个数和数值个数不一样
		return false;
	auto &it = tables.begin();
	for (; it != tables.end(); ++it)
		if (it->tableName == t)    //找到相应表格
			break;
	for (unsigned int i = 0; i < c.size(); ++i)
	{
		unsigned int j = 1;
		for (; j < it->attribute.size(); ++j)
			if (c[i] == it->attribute[j])break;
		if (j == it->attribute.size())return false; //表格中没有该属性
	}
	return true;
}

void User::insertInto()
{
	if (ParseStatement::result.size() < 5)   //指令无效
	{
		cout << "Invalid instruction!" << endl;
		return;
	}
	string tmp = ParseStatement::result[2];

	if (!judge(tmp, "INSERT"))
	{
		cout << "(mysql)==> Permission denied!" << endl;
		return;
	}

	auto &it = tables.begin();
	for (; it != tables.end(); ++it)
		if (it->tableName == tmp)    //找到相应表格
			break;
	if (ParseStatement::result[3] == "VALUES")   //第一种插入方式
	{ 
		int num = it->attribute.size();
		int numOfLine = it->datas.size() + 1;

		if (ParseStatement::result.size() - 3 != num)  //插入属性个数与表格列数不同
		{
			cout << "Format Error!" << endl;
			return;
		}

		Data d;          //在表格中插入该行数据
		d.id = numOfLine;
		for (unsigned int i = 0; i < ParseStatement::result.size() - 4; ++i)
			d.data.push_back(ParseStatement::result[i + 4]);
		it->datas.push_back(d); 

		tmp += ".txt";         //更新相应txt文件
		const char *filename = tmp.c_str();
		ofstream fout;
		fout.open(filename, ios::app);
		fout << numOfLine << '\t';
		unsigned int i = 0;
		for (; i < ParseStatement::result.size() - 4 - 1; ++i)
			fout << ParseStatement::result[i + 4] << '\t';
		fout << ParseStatement::result[i + 4] << endl;
		fout.close();
		return;
	}
	else {
		int numOfLine = it->datas.size() + 1;
		vector<string> column;   //要插入的属性
		unsigned int i = 3;
		for (; ParseStatement::result[i] != "VALUES"; ++i)
			column.push_back(ParseStatement::result[i]);
		vector<string> values;    //要插入的数据
		for (i++; i < ParseStatement::result.size(); ++i)
			values.push_back(ParseStatement::result[i]);

		Data d;          //在表格中插入该行数据
		d.id = numOfLine;
		int h = 0;
		unsigned int j = 1;
		for (; j < it->attribute.size(); ++j)
		{
			if (it->attribute[j] == column[h])
			{
				d.data.push_back(values[h]);
				h++;
				if (h == column.size())
					break;
			}
			else {
				d.data.push_back(" ");
			}
		}
		if (h == column.size())
			for (; j < it->attribute.size() - 1; ++j)
				d.data.push_back(" ");
		it->datas.push_back(d);

		if (!judgeFormat(tmp, column, values))
		{
			cout << "Format Error!" << endl;
			return;
		}


		tmp += ".txt";          //更新相应txt文件 
		const char *filename = tmp.c_str();
		ofstream fout;
		fout.open(filename, ios::app);
		fout << numOfLine << '\t';  //输入ID

		int k = 0; //要插入的第k+1个属性
		unsigned int g = 1;
		for (; g < it->attribute.size() - 1; ++g)
		{
			if (column[k] == it->attribute[g])
			{
				fout << values[k] << '\t';
				++k;
				if (k == column.size())
					break;
			}
			else fout << "\t";
		}
		if (k == column.size())
		{
			for (; g < it->attribute.size() - 1; ++g)
				fout << '\t';
			fout << endl;
		}
		else if (column[k] == it->attribute[g])
			fout << values[k] << endl;
		else fout << endl;
		
		fout.close();
		return;
	}
}