#pragma once
#include"ParseStatement.h"
#include<string>
#include<vector>
#include<iostream>
using namespace std;

#define DROP 0         //ɾ��table����Ӧ�ļ�
#define INSERT 1       //��������
#define DELETE 2       //ɾ��ĳ��
#define SELECT 3       //��ʾĳ��
#define CREATE 4       //����table
#define GRANT 5        //����Ȩ��
#define REVOKE 6       //�ջ���Ȩ
#define TABLELIST 7    //��ӡ��ǰ�û����ܷ��ʵı��Ȩ��
#define cat 8          //�鿴�ļ�

class ParseStatement
{
public:
	static vector<string> result;
	static vector<string> attribute;    //������������
	static void preProcess(string);        //��ָ�����Ԥ����
	static int parse(string);     //���ڽ������ĺ���
};