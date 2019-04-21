#include"Tree.h"

void Tree::setUser(string name)
{
	father->user = name;
}

void myInsert(TNode *node, string locate, string des)  //���ӱ���Ȩ��
{
	if (node->user == locate)
	{
		TNode *add = new TNode;
		add->user = des;
		node->children.push_back(add);
		return;
	}
	for (unsigned int i = 0; i < node->children.size(); ++i)
		myInsert(node->children[i], locate, des);
	return;
}

TNode *Tree::bfs(TNode *node, string des) 
{
	if (node == NULL || node->children.size() == 0)   //Ŀ��ڵ㲻����
		return NULL;
	if (node->user == des)   //�ҵ�Ŀ��ڵ�
		return node;
	for (vector<TNode*>::iterator it = node->children.begin(); it != node->children.end(); it++)
		return bfs(*it, des);   //�ݹ����
}

void Tree::deleteMemory(TNode *&node)  
{
	if (node == NULL || node->children.size() == 0)  
		return;
	TNode *tmp = node;
	delete node;
	for (vector<TNode*>::iterator it = tmp->children.begin(); it != tmp->children.end(); it++)
		deleteMemory(*it);
}

void Tree::insertAfter(string locate, string des)
{
	myInsert(father, locate, des);
}

bool Tree::deleteNode(string withdraw, string beWithdraw)
{
	TNode *tn1 = bfs(father, withdraw); //�ҵ��ջ�Ȩ����
	if(tn1==NULL)   //�ջ�Ȩ���߻��ջ�Ȩ���߲�����
		return false;
	TNode *tn2 = bfs(tn1, beWithdraw); //�ҵ����ջ�Ȩ����
	if (tn2 == NULL)  //���ջ�Ȩ���߲�����
		return false;
	TNode *tmp = tn2;
	for (unsigned int i = 0; i < tn1->children.size();++i)
		if (tn1->children[i] == tn2)
		{
			tn1->children[i] = NULL;  //�ջ�Ȩ��
			break;
		}
	deleteMemory(tmp);  //�ͷű��ջ��߿ռ�
	return true;
}