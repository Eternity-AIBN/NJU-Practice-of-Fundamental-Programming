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
	TNode *bfs(TNode *node, string des);   //广度搜索，找到收回权限和被收回权限者
	TNode *bfs2(TNode *node, string des);
	void deleteMemory(TNode *&node);  //释放被删除子树空间
	static void treeRevoke(TNode *firstUser, vector<string> &list);

//private:
	TNode *father;
};