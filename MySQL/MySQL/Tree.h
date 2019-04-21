#pragma once
#include<vector>
#include<cstdlib>
#include<iostream>
using namespace std;

struct TNode
{
	string user;
	vector<TNode*> children;
};

class Tree
{
public:
	Tree() { father = new TNode; }
	void setUser(string name);
	~Tree() {}
	void insertAfter(string locate, string des);
	bool deleteNode(string withdraw, string beWithdraw);
	TNode *bfs(TNode *node, string des);   //����������ҵ��ջ�Ȩ�޺ͱ��ջ�Ȩ����
	void deleteMemory(TNode *&node);  //�ͷű�ɾ�������ռ�

private:
	TNode *father;
};