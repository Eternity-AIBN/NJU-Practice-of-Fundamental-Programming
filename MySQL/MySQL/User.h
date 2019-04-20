#pragma once
#include"ParseStatement.h"
#include"Permission.h"
#include"Table.h"
#include<iostream>
#include<fstream>
using namespace std;

struct UserInfo    //用户信息
{
	string userName;     //用户名
	string password;     //密码
	bool permission[4];  //四个操作权限
};

class User
{
	UserInfo info;
public:
	static int n;  //当前登陆的是第几个用户
	vector<permissionOfAUser> pofUser; //一个用户在所有表格上的权限
	User() {}
	void operator=(UserInfo tmp) { info = tmp; }
	UserInfo &getInfo() { return info; }
	static int login();           //用户登录
	bool createTable();     //创建table
	void dropTable();       //删除table及相应文件
	void tableList();       //打印当前用户所能访问的表和权限
	void insertInto();      //插入数据
	void deleteFrom();      //删除某行
	void selectFrom();      //显示某列
	void grant();           //授予权限
	void revoke();          //收回授权
	static void run();    

};

extern User user[8];
extern vector<Table> tables;
//vector<User> users;   //用户列表