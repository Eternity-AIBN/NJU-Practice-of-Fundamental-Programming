#pragma once
#include"ParseStatement.h"
#include<string>
#include<vector>
#include<iostream>
using namespace std;

#define DROP 0         //删除table及相应文件
#define INSERT 1       //插入数据
#define DELETE 2       //删除某行
#define SELECT 3       //显示某列
#define CREATE 4       //创建table
#define GRANT 5        //授予权限
#define REVOKE 6       //收回授权
#define TABLELIST 7    //打印当前用户所能访问的表和权限
#define cat 8          //查看文件

class ParseStatement
{
public:
	static vector<string> result;
	static vector<string> attribute;    //储存读入的属性
	static void preProcess(string);        //对指令进行预处理
	static int parse(string);     //用于解析语句的函数
};