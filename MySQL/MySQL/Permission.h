#pragma once
#include"Tree.h"
#include<string>
#include<vector>
using namespace std;

struct singlePermission    //储存具有某个权限的所有用户
{
	string permissionName;   //权限名
	Tree permissionTree;     //用户权限列表(树)
};

struct Permission         //与某个表格相关的所有用户权限
{
	string tableName;   //表格名
	string owner;       //表的所有者
	singlePermission permissionList[4];   //权限列表
};

struct permissionOfAUser
{
	string tableName;   //表格名
	bool isOwner;        //是否是表的拥有者
	vector<string> perm;  //所有的权限
};