#pragma once
#include<string>
#include<vector>
using namespace std;

struct Data   //一行数据
{
	int id;
	vector<string> data;
};

struct Table
{
	string tableName;   //表格名
	vector<string> attribute;  //属性名
	vector<Data> datas;   //表格所有数据信息   
};
