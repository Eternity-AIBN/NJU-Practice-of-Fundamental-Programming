#pragma once
#include<string>
#include<vector>
using namespace std;

struct Data   //һ������
{
	int id;
	vector<string> data;
};

struct Table
{
	string tableName;   //�����
	vector<string> attribute;  //������
	vector<Data> datas;   //�������������Ϣ   
};
