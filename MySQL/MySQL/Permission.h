#pragma once
#include"Tree.h"
#include<string>
#include<vector>
using namespace std;

struct singlePermission    //�������ĳ��Ȩ�޵������û�
{
	string permissionName;   //Ȩ����
	Tree permissionTree;     //�û�Ȩ���б�(��)
};

struct Permission         //��ĳ�������ص������û�Ȩ��
{
	string tableName;   //�����
	string owner;       //���������
	vector<singlePermission> permissionList;   //Ȩ���б�
};

vector<Permission> allThePermission;  //���б���Ȩ��