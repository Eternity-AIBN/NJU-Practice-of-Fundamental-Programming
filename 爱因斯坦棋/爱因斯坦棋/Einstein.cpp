#define _CRT_SECURE_NO_WARNINGS
#include "Einstein.h"
#include<iostream>
#include<cctype>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<sstream>
#include<fstream>
#include<cmath>
using namespace std;
#define blue 1
#define red 0

typedef pair<int, int> moveWay;  //���ӷ��򣬴ӵ�һ�������ߵ��ڶ�������
bool checkOrNot = false; //�Ƿ�����ַ����ܴ�仯
int toCheck[25];  //��¼��һ����������̣����ڶԱȼ���Ƿ��¿���
bool mycolor;//��¼�ҷ���ɫ��0Ϊ�죬1Ϊ��
int moveIndex;
string moveDir;
bool IamWin = false;
char startTime[64];
bool recordTime = true;

inline void updateBoard(int chessboard[], int n) //�������
{
	/*���Ż�*/

	if (moveDir == "up")
		chessboard[moveIndex - 5] = chessboard[moveIndex];
	else if(moveDir == "left")
		chessboard[moveIndex - 1] = chessboard[moveIndex];
	else if (moveDir == "leftup")
		chessboard[moveIndex - 6] = chessboard[moveIndex];
	else if (moveDir == "down")
		chessboard[moveIndex + 5] = chessboard[moveIndex];
	else if (moveDir == "right")
		chessboard[moveIndex + 1] = chessboard[moveIndex];
	else if (moveDir == "rightdown")
		chessboard[moveIndex + 6] = chessboard[moveIndex];
	chessboard[moveIndex] = 0;
}

inline bool check(int chessboard[], int n)  //�������Ƿ����޴�仯�����¿��֣�
{
	int diff = 0;//ͳ��0�ĸ���
	for (int i = 0; i < 25; ++i)
		if (chessboard[i] != toCheck[i])diff++;
	if (diff > 2)return true;
	else return false;
}

int isWin(int chessboard[], int n, bool c)  //�ж�ĳ���Ƿ�ȡʤ
{
	//����ʤ2���췽ʤ1��δ����0

	//�ж���ɫ���Ƿ��ʤ
	if (c)
	{
		if (chessboard[0] > 6)return 2; //�ߵ��췽�������ǵ�
		int num = 0; //�췽ʣ��
		for (int i = 0; i < 25; ++i)
			if (chessboard[i] != 0 && chessboard[i] <= 6)num++;
		if (num == 0)return 2;
		return 0;
	}
	//�жϺ�ɫ���Ƿ��ʤ
	else {
		if (chessboard[24] != 0 && chessboard[24] <= 6)return 1; //�ߵ������������ǵ�
		int num = 0; //����ʣ��
		for (int i = 0; i < 25; ++i)
			if (chessboard[i] > 6)num++;
		if (num == 0)return 1;
		return 0;
	}
}


void randMove(int chessboard[], int n, int &dice, bool color)
{
	int jj = -1; //ѡ��Ҫ�ߵ���
	int index[2]; //�����ӵ�λ��
	index[0] = -1, index[1] = -1;

	for (int i = 0; i < 25; ++i)
		if (chessboard[i] == dice)  //��ɫ�ӵ�����ͬ�����ӻ���������
		{
			index[0] = i;
			jj = 0;
			break;
		}
	if (jj == -1)   //��ɫ�ӵ�����ͬ�����Ӳ���������
	{
		int mindis1 = 25, mindis2 = 25;
		int tmpdis1, tmpdis2;
		if (color == blue)
		{
			for (int i = 0; i < 25; ++i)
				if (chessboard[i]>dice)  //�ҵ�����ɫ�ӵ�����������ӽ�����������λ��
				{
					tmpdis1 = chessboard[i] - dice;
					if (tmpdis1 < mindis1)
					{
						mindis1 = tmpdis1;
						index[0] = i;
						jj = 0;
					}
				}
				else if (chessboard[i]>6) //�ҵ�С��ɫ�ӵ�����������ӽ�����������λ��
				{
					tmpdis2 = dice - chessboard[i];
					if (tmpdis2 < mindis1)
					{
						mindis2 = tmpdis2;
						index[1] = i;
						jj = 1;
					}
				}
		}
		else {
			for (int i = 0; i < 25; ++i)
				if (chessboard[i] <= 6 && chessboard[i]>dice)  //�ҵ�����ɫ�ӵ�����������ӽ�����������λ��
				{
					tmpdis1 = chessboard[i] - dice;
					if (tmpdis1 < mindis1)
					{
						mindis1 = tmpdis1;
						index[0] = i;
						jj = 0;
					}
				}
				else if (chessboard[i]>0 && chessboard[i] < dice) //�ҵ�С��ɫ�ӵ�����������ӽ�����������λ��
				{
					tmpdis2 = dice - chessboard[i];
					if (tmpdis2 < mindis1)
					{
						mindis2 = tmpdis2;
						index[1] = i;
						jj = 1;
					}
				}
		}

		if (index[0] != -1 && index[1] != -1) //������������
			jj = rand() % 2;
	}

	vector<int> ways;  //�ƶ�������-1��ʾ����
	if (color == blue)
	{
		if (index[jj] > 4)
			ways.push_back(-5); //����
		if (index[jj] % 5 != 0)
			ways.push_back(-1); //����
		if (ways.size() == 2)
			ways.push_back(-6); //������
		int i = rand() % ways.size();

		chessboard[index[jj] + ways[i]] = chessboard[index[jj]];
		chessboard[index[jj]] = 0; //�߿���ԭ���ĵط����������ӣ���Ϊ0
		return;
	}
	else {
		if (index[jj] < 20)
			ways.push_back(5); //����
		if (index[jj] % 5 != 4)
			ways.push_back(1); //����
		if (ways.size() == 2)
			ways.push_back(6); //������
		int i = rand() % ways.size();

		chessboard[index[jj] + ways[i]] = chessboard[index[jj]];
		chessboard[index[jj]] = 0; //�߿���ԭ���ĵط����������ӣ���Ϊ0
	}
}

struct Node
{
	int total, win; //��¼ĳ�ڵ���ʴ����Լ���ʤ����
	Node *father;  //���ڻ���ʱ�ҵ����ڵ�
	vector<Node*> child;  //��һ���Ľڵ�
	bool color;  //�ýڵ����巽��ɫ
	int curBoard[25];  //��¼�ýڵ�����״̬
	Node(moveWay m, bool c) { father = NULL; total = 0; win = 0; color = c; moveway = m; }
	Node(bool c) { father = NULL; total = 0; win = 0; color = c; moveway.first = -1; moveway.second = -1; }

	moveWay moveway; //�������״̬���ƶ���ʽ������Ϊ��-1��-1��
	vector<moveWay> allMove;  //���п��ƶ��ķ�ʽ

    //���ݸýڵ�������Ϣ����allMove������expand��
	void handle()  
	{
		allMove.clear();
		moveWay tmp;
		vector<int> position; //�ýڵ��Ӧcolor���ڵ�ǰ�������������ӵ�λ��
		if (color == blue)
		{
			for (int i = 0; i < 25; ++i)
				if (curBoard[i] > 6)
					position.push_back(i);
			for (auto it : position)
			{
				if (it > 4)  //�����ƶ�
				{
					tmp.first = it;
					tmp.second = it - 5;
					allMove.push_back(tmp);
				}
				if (it % 5 != 0)  //�����ƶ�
				{
					tmp.first = it;
					tmp.second = it - 1;
					allMove.push_back(tmp);
				}
				if (it > 4 && it % 5 != 0) //�������ƶ�
				{
					tmp.first = it;
					tmp.second = it - 6;
					allMove.push_back(tmp);
				}
			}
			return;
		}
		else {
			for (int i = 0; i < 25; ++i)
				if (curBoard[i] != 0 && curBoard[i] <= 6)
					position.push_back(i);
			for (auto it : position)
			{
				if (it < 20)  //�����ƶ�
				{
					tmp.first = it;
					tmp.second = it + 5;
					allMove.push_back(tmp);
				}
				if (it % 5 != 4)  //�����ƶ�
				{
					tmp.first = it;
					tmp.second = it + 1;
					allMove.push_back(tmp);
				}
				if (it < 20 && it % 5 != 4) //�������ƶ�
				{
					tmp.first = it;
					tmp.second = it + 6;
					allMove.push_back(tmp);
				}
			}
			return;
		}
	}
	//���ݸýڵ�������Ϣ����allMove�����ڸ���root�ڵ㣩
	void handle(int &dice)  
	{
		allMove.clear();
		moveWay tmpMove;
		int j = 0; //�����ӵĸ���
		int index[2]; //�����ӵ�λ��
		index[0] = -1, index[1] = -1;

		for (int i = 0; i < 25; ++i)
			if (curBoard[i] == dice)  //��ɫ�ӵ�����ͬ�����ӻ���������
			{
				index[0] = i;
				j = 1;
				break;
			}
		if (j == 0)   //��ɫ�ӵ�����ͬ�����Ӳ���������
		{
			j = 1;
			int mindis1 = 25, mindis2 = 25;
			int tmpdis1, tmpdis2;
			if (color == blue)
			{
				for (int i = 0; i < 25; ++i)
					if (curBoard[i]>dice)  //�ҵ�����ɫ�ӵ�����������ӽ�����������λ��
					{
						tmpdis1 = curBoard[i] - dice;
						if (tmpdis1 < mindis1)
						{
							mindis1 = tmpdis1;
							index[0] = i;
						}
					}
					else if (curBoard[i]>6) //�ҵ�С��ɫ�ӵ�����������ӽ�����������λ��
					{
						tmpdis2 = dice - curBoard[i];
						if (tmpdis2 < mindis2)
						{
							mindis2 = tmpdis2;
							index[1] = i;
						}
					}
				if (index[0] != -1 && index[1] != -1)
					j = 2;
			}
			else {
				for (int i = 0; i < 25; ++i)
					if (curBoard[i] <= 6 && curBoard[i]>dice)  //�ҵ�����ɫ�ӵ�����������ӽ�����������λ��
					{
						tmpdis1 = curBoard[i] - dice;
						if (tmpdis1 < mindis1)
						{
							mindis1 = tmpdis1;
							index[0] = i;
						}
					}
					else if (curBoard[i]>0 && curBoard[i] < dice) //�ҵ�С��ɫ�ӵ�����������ӽ�����������λ��
					{
						tmpdis2 = dice - curBoard[i];
						if (tmpdis2 < mindis2)
						{
							mindis2 = tmpdis2;
							index[1] = i;
						}
					}
				if (index[0] != -1 && index[1] != -1)
					j = 2;
			}
		}
		if (index[0] == -1)
			index[0] = index[1];
		if (color == blue)//�Կ��ƶ����ӽ��д����õ����ƶ�����
			for (int k = 0; k < j; ++k)
			{
				if (index[k] > 4)  //����
				{
					tmpMove.first = index[k];
					tmpMove.second = index[k] - 5;
					allMove.push_back(tmpMove);
				}
				if (index[k] % 5 != 0)  //����
				{
					tmpMove.first = index[k];
					tmpMove.second = index[k] - 1;
					allMove.push_back(tmpMove);
				}
				if (index[k] > 4 && index[k] % 5 != 0)  //������
				{
					tmpMove.first = index[k];
					tmpMove.second = index[k] - 6;
					allMove.push_back(tmpMove);
				}
			}
		else for (int k = 0; k < j; ++k)
		{
			if (index[k] < 20)  //����
			{
				tmpMove.first = index[k];
				tmpMove.second = index[k] + 5;
				allMove.push_back(tmpMove);
			}
			if (index[k] % 5 != 4)  //����
			{
				tmpMove.first = index[k];
				tmpMove.second = index[k] + 1;
				allMove.push_back(tmpMove);
			}
			if (index[k] < 20 && index[k] % 5 != 4)  //������
			{
				tmpMove.first = index[k];
				tmpMove.second = index[k] + 6;
				allMove.push_back(tmpMove);
			}
		}
	}
};
class Tree
{
	Node *root; //���ڵ�,����ǰ������

public:
	bool color; //�ҷ���ɫ
	Node *init; //���ֽڵ�
	Tree() { root = NULL; }

	string UCTSearch(int a[], int n, int dice);  //���ز���

	Node *treePolicy();   //�����ԣ���������ģ��Ľڵ㣨����չ�ڵ�or����ӽڵ㣩
	Node *expand(Node *p); //ѡ��δ�����ľ��棬��Ϊ����չ�Ľڵ㷵��
	Node *bestChild(Node *p, double c = 1.96); //����UCB��ʽѡ��p�ڵ��µ�����ӽڵ�
											   /*����c��Ҫ�𣿣���*/

	bool rolloutPolicy(Node *p);  //ģ�⣬�������һ���壬�����ؽ��
	void backUp(Node *p, bool result);  //���ݣ����¸��ڵ㵽p�ڵ���һ·�����нڵ��ʤ����Ϣ

	void moveByOpponent(int a[], int n, int dice);  //�Է����Ӻ���¸��ڵ�
												
}uct;

string Tree::UCTSearch(int a[], int n, int dice)
{
	time_t init, now;
	init = clock();

	moveByOpponent(a, 25, dice);//���¸��ڵ�

	//int coo = 1;

	now = clock();//(double)(t2 - t1)/ CLOCKS_PER_SEC * 1000
	while (((double)(now - init) / CLOCKS_PER_SEC) < 4.75)//δ��ʱ
	{
		//�Ѷ���������һ��???
		//cout << "��" << coo << "������" << endl;
		Node *simulate = treePolicy();
		//cout << "��" << coo << "��treePolicy���" << endl;
		bool result = rolloutPolicy(simulate);
		//cout << "��" << coo << "��rolloutPolicy���" << endl;
		backUp(simulate, result);
		//cout << "��" << coo << "��backUp���" << endl;
		//coo++;
		now = clock();
	}
	Node *best = NULL;
	double aaaa = -RAND_MAX;
	for(auto it:root->child)
		if ((double)(it->win/it->total) > aaaa)
		{
			aaaa = 1.0*(it->win/it->total);
			best = it;
		}

	int p[2];  //������ӵ�����λ��
	for (int i = 0, diff = 0; diff < 2; ++i)
		if (best->curBoard[i] != root->curBoard[i])
		{
			p[diff] = i;
			diff++;
		}

	int dis = p[1] - p[0];
	string ans;
	stringstream ss;
	if (color == blue)
	{
		moveIndex = p[1];
		ss << best->curBoard[p[0]];
		ss >> ans;
		switch (dis)
		{
		case 1:ans += "|left"; moveDir = "left"; break;
		case 5:ans += "|up"; moveDir = "up"; break;
		case 6:ans += "|leftup"; moveDir = "leftup"; break;
		default:
			break;
		}
	}
	else {
		moveIndex = p[0];
		ss << best->curBoard[p[1]];
		ss >> ans;
		switch (dis)
		{
		case 1:ans += "|right"; moveDir = "right"; break;
		case 5:ans += "|down"; moveDir = "down"; break;
		case 6:ans += "|rightdown"; moveDir = "rightdown"; break;
		default:
			break;
		}
	}
	//moveByMe
	root = best; //�ҷ����Ӻ���¸��ڵ�
	
	return ans;
}

Node *Tree::treePolicy()
{
	Node *presentNode = root;
	while (!isWin(presentNode->curBoard, 25, !presentNode->color))//�ڵ㲻����ֹ�ڵ�
	{
		if (presentNode->child.size() != presentNode->allMove.size()) //�ýڵ����չ
			return expand(presentNode);  //��չ�ýڵ�
		else presentNode = bestChild(presentNode);
	}
	return presentNode;
}

Node *Tree::expand(Node *p) //��չ�ڵ�p��������չ�Ľڵ�ӵ�p���ӽڵ��У�������չ�Ľڵ�
{
	vector<moveWay> vaildMove;  //δ���������ӷ�ʽ
	Node *expandNode;
	bool flag;
	for (auto it : p->allMove)
	{
		flag = false;  //ĳһ�ƶ���ʽ�Ƿ��Ѿ�ģ��
		for (auto itt : p->child)
			if (itt->moveway == it)
			{
				flag = true;
				break;
			}
		if (!flag)  //�÷�ʽδģ��
			vaildMove.push_back(it);
	}

	int num = rand() % vaildMove.size();
	
	moveWay tmpWay = vaildMove[num];
	int tmpBoard[25];
	for (int i = 0; i < 25; ++i)
		tmpBoard[i] = p->curBoard[i];
	tmpBoard[tmpWay.second] = tmpBoard[tmpWay.first];
	tmpBoard[tmpWay.first] = 0;

	expandNode = new Node(tmpWay, !p->color);
	expandNode->father = p;
	for (int i = 0; i < 25; ++i)
		expandNode->curBoard[i] = tmpBoard[i];
	expandNode->handle();

	p->child.push_back(expandNode);
	return expandNode;
}

void Tree::moveByOpponent(int a[], int n, int dice)
{
	if (init == NULL) //�տ���
	{
		root = new Node(mycolor);
		root->father = root;
		init = root;
		for (int i = 0; i < 25; ++i)
			root->curBoard[i] = a[i];
		root->handle(dice);
		return;
	}

	for (auto it : root->child)
	{
		int i = 0;
		for (; i < 25; ++i)
			if (it->curBoard[i] != a[i])break;

		if (i == 25)  //�����µ����ҷ��Ѿ�ģ���
		{
			root = it;
			root->handle(dice);
			bool flag2;
			for (auto itt = root->child.begin(); itt != root->child.end();)
			{
				flag2 = false;
				for (auto allMoveWay : root->allMove)
					if ((*itt)->moveway == allMoveWay) {
						flag2 = true;
						break;
					}
				if (!flag2)
					itt = root->child.erase(itt);
				else itt++;
			}
			return;
		}
	}

	//�����µ����ҷ�δģ���
	Node *p = new Node(!color);
	p->father = root;
	for (int i = 0; i < 25; ++i)
		p->curBoard[i] = a[i];
	p->handle(dice);
	root = p;
}

void Tree::backUp(Node *p, bool result)
{
	while (p != root)  //�ǲ��ǻ�����==root???
	{
		p->total++;
		p->win += result;
		result = !result;
		p = p->father;
	}
	p->total++;
	p->win += result;
}

bool Tree::rolloutPolicy(Node *p)
{
	bool whoseTurn = p->color;  //�ֵ�˭��
	int board[25];
	for (int i = 0; i < 25; ++i)
		board[i] = p->curBoard[i];
	while (!isWin(board, 25, !whoseTurn))  //δ����ʤ��
	{
		int dice = 1 + rand() % 6; //ɫ�ӵ���
		if (whoseTurn == blue)
			dice += 6;
		randMove(board, 25, dice, whoseTurn);
		whoseTurn = !whoseTurn;
	}
	if (isWin(board, 25, !whoseTurn) == 1)  //�췽ʤ
		return red;
	else return blue;  //����ʤ
}

Node *Tree::bestChild(Node *p, double c)
{
	//c = 1.96;//���޸�

	double argmax = -RAND_MAX, ucb;
	Node *best = NULL;
	for (auto it : p->child)
	{
		//ucb = 1.0*it->win / it->total + c*sqrt(log(p->total) / it->total);
		ucb = 1.0*it->win / it->total + 1.38*sqrt(2 * log(p->total) / it->total);
		if (ucb > argmax) {
			argmax = ucb;
			best = it;
		}
	}
	return best;
}




Einstein::Einstein()
{
	srand((unsigned)time(NULL));
	this->clientsocket.connectServer();
	clientsocket.sendMsg(ID);
}

Einstein::~Einstein()
{
	this->clientsocket.close();
}

int Einstein::parse(std::string s)
{
	if (s == "close")return -1;  //���ֽ������˳���Ϸ
	auto it = s.begin();
	for (int i = 0; i < 25;)
	{
		if (isdigit(*it))
		{
			chessboard[i] = *it - '0';
			it++;
			if (isdigit(*it))
			{
				chessboard[i] = chessboard[i] * 10 + *it - '0';
				it++;
			}
			++i;
		}
		else it++;
	}
	it += 3;
	dice = *it - '0';
	it++;
	if (it != s.end())
		dice = dice * 10 + *it - '0';
	if (dice > 6)
		mycolor = blue;
	else mycolor = red;
	return 0;
}

int Einstein::handle()
{
	clientsocket.recvMsg();

	if (parse(clientsocket.getRecvMsg()) == -1)  //������Ϣ����������
	{
		if (!IamWin)
			logging("Result: OpponentWin");
		return 0;
	}
	uct.color = mycolor;
	IamWin = false;

	//�տ��ֵ�һ������Ҫ��飬��ʱcheckOrNotΪfalse
	if (checkOrNot)   //���Է��Ƿ��ʤ�������¿���
		if (check(chessboard, 25)) //ȷʵ���¿���,�ҷ����һ��
		{
			logging("Result: OpponentWin");
			uct.init = NULL;
			checkOrNot = false;
		}

	//���Ժ���
	string ans = uct.UCTSearch(chessboard, 25, dice);

	//logging(ans);  //����ս��¼������ն˲��浽list������

	clientsocket.sendMsg(ans.c_str());  //������Ϣ�������ж�

	logging(ans);  //����ս��¼������ն˲��浽list������

	updateBoard(chessboard, 25);

	if (isWin(chessboard, 25, mycolor) != 0) {
		checkOrNot = false;  //�ҷ���ʤ���¼���������¿���������
		IamWin = true;
		logging("Result: YouWin");
		uct.init = NULL;
	}
	else checkOrNot = true;  //�ӵڶ����忪ʼ���

	for (int i = 0; i < 25; ++i)  //��¼��ǰ����
		toCheck[i] = chessboard[i];

	return 1;
}

int Einstein::logging(std::string s)
{
	char c[64];
	time_t timep;
	time(&timep);
	strftime(c, sizeof(c), "%Y-%m-%d %H-%M-%S", localtime(&timep));

	if (recordTime)
	{
		int i = 0;
		for (; c[i] != '\0'; ++i)
			startTime[i] = c[i];
		startTime[i] = '\0';
		recordTime = false;
	}

	if (s[0] == 'd')  //done
	{
		s = ": " + s;
		s = c + s + '\n';
		cout << s;
		logger.push_back(s);
		return 0;
	}

	if (s[0] == 'R')  //Result
	{
		recordTime = true;

		int day1, hour1, minute1, second1;
		stringstream ss[8];
		ss[0] << startTime[8] << startTime[9];
		ss[0] >> day1;
		ss[1] << startTime[11] << startTime[12];
		ss[1] >> hour1;
		ss[2] << startTime[14] << startTime[15];
		ss[2] >> minute1;
		ss[3] << startTime[17] << startTime[18];
		ss[3] >> second1;

		int day2, hour2, minute2, second2;
		ss[4] << c[8] << c[9];
		ss[4] >> day2;
		ss[5] << c[11] << c[12];
		ss[5] >> hour2;
		ss[6] << c[14] << c[15];
		ss[6] >> minute2;
		ss[7] << c[17] << c[18];
		ss[7] >> second2;

		int costTime = (day2 - day1) * 86400 + (hour2 - hour1) * 3600 + (minute2 - minute1) * 60 + second2 - second1;
		stringstream sss;
		sss << costTime;
		string a;
		sss >> a;

		s = ": " + s;
		s = c + s + "   Use time: " + a + " seconds\n";

		cout << s;
		logger.push_back(s);
		return 0;
	}


	string tmp = ": ";
	string p = clientsocket.getRecvMsg();
	auto it = p.begin();
	for (; it != p.end() && *it != '|'; ++it)
		tmp.push_back(*it);
	if (it == p.end())
	{
		tmp = c + tmp;
		cout << tmp;
		logger.push_back(tmp);
		return 0;
	}

	tmp += " ||chess&move: " + s;
	tmp = c + tmp + '\n';

	cout << tmp;
	logger.push_back(tmp);
	return 0;
}

int Einstein::writelog()
{
	auto it = logger.begin();
	filename.assign(*it, 0, 10);
	filename += "-181860044.log";
	ofstream fout(filename,ios::app);
	for (; it != logger.end(); ++it)
		fout << *it;
	fout << endl;
	fout.close();
	return 0;
}
