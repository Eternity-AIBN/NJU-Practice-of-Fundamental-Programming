#pragma once
#include<vector>
#include<cstdlib>
#include<iostream>
#include<string>
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
	void deleteNode(string withdraw, string beWithdraw);
	TNode *bfs(TNode *node, string des);   //����������ҵ��ջ�Ȩ�޺ͱ��ջ�Ȩ����
	TNode *bfs2(TNode *node, string des);
	void deleteMemory(TNode *&node);  //�ͷű�ɾ�������ռ�
	static void treeRevoke(TNode *firstUser, vector<string> &list);

//private:
	TNode *father;
};