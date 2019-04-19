#pragma once
#include"ParseStatement.h"
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
	User() {}
	void operator=(UserInfo tmp) { info = tmp; }
	UserInfo getInfo() { return info; }
	static int login();           //�û���¼
	bool createTable();     //����table
	void dropTable();       //ɾ��table����Ӧ�ļ�
	void tableList();       //��ӡ��ǰ�û����ܷ��ʵı���Ȩ��
	void insertInto();      //��������
	void deleteFrom();      //ɾ��ĳ��
	void selectFrom();      //��ʾĳ��
	void grant();           //����Ȩ��
	void revoke();          //�ջ���Ȩ
	static void run(int n);    

};

//vector<User> users;   //�û��б�