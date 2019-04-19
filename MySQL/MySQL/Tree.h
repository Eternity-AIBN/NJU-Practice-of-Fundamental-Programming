#pragma once
#include<vector>
using namespace std;

struct TNode
{
	string user;
	vector<TNode*> children;
};

class Tree
{
public:
	Tree() {
		father = new TNode;
	}
	~Tree();
	/*void insert_at_root(int x);
	void insert_after(int x, int y);
	void delete_node(int x);
	void print(int n);*/

private:
	TNode *father;
};