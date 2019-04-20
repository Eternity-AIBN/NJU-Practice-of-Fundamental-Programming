#pragma once
#include"ParseStatement.h"
#include"Permission.h"
#include"Table.h"
#include<iostream>
#include<fstream>
using namespace std;

struct UserInfo    //�û���Ϣ
{
	string userName;     //�û���
	string password;     //����
	bool permission[4];  //�ĸ�����Ȩ��
};

class User
{
	UserInfo info;
public:
	static int n;  //��ǰ��½���ǵڼ����û�
	vector<permissionOfAUser> pofUser; //һ���û������б���ϵ�Ȩ��
	User() {}
	void operator=(UserInfo tmp) { info = tmp; }
	UserInfo &getInfo() { return info; }
	static int login();           //�û���¼
	bool createTable();     //����table
	void dropTable();       //ɾ��table����Ӧ�ļ�
	void tableList();       //��ӡ��ǰ�û����ܷ��ʵı��Ȩ��
	void insertInto();      //��������
	void deleteFrom();      //ɾ��ĳ��
	void selectFrom();      //��ʾĳ��
	void grant();           //����Ȩ��
	void revoke();          //�ջ���Ȩ
	static void run();    

};

extern User user[8];
extern vector<Table> tables;
//vector<User> users;   //�û��б�