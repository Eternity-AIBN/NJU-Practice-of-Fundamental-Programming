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
	singlePermission permissionList[4];   //Ȩ���б�
};

struct permissionOfAUser
{
	string tableName;   //�����
	bool isOwner;        //�Ƿ��Ǳ��ӵ����
	vector<string> perm;  //���е�Ȩ��
};