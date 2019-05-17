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

typedef pair<int, int> moveWay;  //走子方向，从第一个坐标走到第二个坐标
bool checkOrNot = false; //是否检查棋局发生很大变化
int toCheck[25];  //记录上一步下完的棋盘，用于对比检查是否新开局
bool mycolor;//记录我方颜色，0为红，1为蓝
int moveIndex;
string moveDir;
bool IamWin = false;
char startTime[64];
bool recordTime = true;

inline void updateBoard(int chessboard[], int n) //更新棋局
{
	/*待优化*/

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

inline bool check(int chessboard[], int n)  //检查棋局是否发生巨大变化（重新开局）
{
	int diff = 0;//统计0的个数
	for (int i = 0; i < 25; ++i)
		if (chessboard[i] != toCheck[i])diff++;
	if (diff > 2)return true;
	else return false;
}

int isWin(int chessboard[], int n, bool c)  //判断某方是否取胜
{
	//蓝方胜2，红方胜1，未结束0

	//判断蓝色方是否获胜
	if (c)
	{
		if (chessboard[0] > 6)return 2; //走到红方出发区角点
		int num = 0; //红方剩子
		for (int i = 0; i < 25; ++i)
			if (chessboard[i] != 0 && chessboard[i] <= 6)num++;
		if (num == 0)return 2;
		return 0;
	}
	//判断红色方是否获胜
	else {
		if (chessboard[24] != 0 && chessboard[24] <= 6)return 1; //走到蓝方出发区角点
		int num = 0; //蓝方剩子
		for (int i = 0; i < 25; ++i)
			if (chessboard[i] > 6)num++;
		if (num == 0)return 1;
		return 0;
	}
}


void randMove(int chessboard[], int n, int &dice, bool color)
{
	int jj = -1; //选择要走的子
	int index[2]; //可下子的位置
	index[0] = -1, index[1] = -1;

	for (int i = 0; i < 25; ++i)
		if (chessboard[i] == dice)  //与色子点数相同的棋子还在棋盘上
		{
			index[0] = i;
			jj = 0;
			break;
		}
	if (jj == -1)   //与色子点数相同的棋子不在棋盘上
	{
		int mindis1 = 25, mindis2 = 25;
		int tmpdis1, tmpdis2;
		if (color == blue)
		{
			for (int i = 0; i < 25; ++i)
				if (chessboard[i]>dice)  //找到大于色子点数的与其最接近的棋子所在位置
				{
					tmpdis1 = chessboard[i] - dice;
					if (tmpdis1 < mindis1)
					{
						mindis1 = tmpdis1;
						index[0] = i;
						jj = 0;
					}
				}
				else if (chessboard[i]>6) //找到小于色子点数的与其最接近的棋子所在位置
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
				if (chessboard[i] <= 6 && chessboard[i]>dice)  //找到大于色子点数的与其最接近的棋子所在位置
				{
					tmpdis1 = chessboard[i] - dice;
					if (tmpdis1 < mindis1)
					{
						mindis1 = tmpdis1;
						index[0] = i;
						jj = 0;
					}
				}
				else if (chessboard[i]>0 && chessboard[i] < dice) //找到小于色子点数的与其最接近的棋子所在位置
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

		if (index[0] != -1 && index[1] != -1) //可走子有两个
			jj = rand() % 2;
	}

	vector<int> ways;  //移动方向，如-1表示向左
	if (color == blue)
	{
		if (index[jj] > 4)
			ways.push_back(-5); //向上
		if (index[jj] % 5 != 0)
			ways.push_back(-1); //向左
		if (ways.size() == 2)
			ways.push_back(-6); //向左上
		int i = rand() % ways.size();

		chessboard[index[jj] + ways[i]] = chessboard[index[jj]];
		chessboard[index[jj]] = 0; //走开后原来的地方不再有棋子，变为0
		return;
	}
	else {
		if (index[jj] < 20)
			ways.push_back(5); //向下
		if (index[jj] % 5 != 4)
			ways.push_back(1); //向右
		if (ways.size() == 2)
			ways.push_back(6); //向右下
		int i = rand() % ways.size();

		chessboard[index[jj] + ways[i]] = chessboard[index[jj]];
		chessboard[index[jj]] = 0; //走开后原来的地方不再有棋子，变为0
	}
}

struct Node
{
	int total, win; //记录某节点访问次数以及获胜次数
	Node *father;  //用于回溯时找到父节点
	vector<Node*> child;  //下一步的节点
	bool color;  //该节点下棋方颜色
	int curBoard[25];  //记录该节点棋盘状态
	Node(moveWay m, bool c) { father = NULL; total = 0; win = 0; color = c; moveway = m; }
	Node(bool c) { father = NULL; total = 0; win = 0; color = c; moveway.first = -1; moveway.second = -1; }

	moveWay moveway; //到达这个状态的移动方式，开局为（-1，-1）
	vector<moveWay> allMove;  //所有可移动的方式

    //根据该节点棋盘信息更新allMove（用于expand）
	void handle()  
	{
		allMove.clear();
		moveWay tmp;
		vector<int> position; //该节点对应color方在当前棋盘上所有棋子的位置
		if (color == blue)
		{
			for (int i = 0; i < 25; ++i)
				if (curBoard[i] > 6)
					position.push_back(i);
			for (auto it : position)
			{
				if (it > 4)  //向上移动
				{
					tmp.first = it;
					tmp.second = it - 5;
					allMove.push_back(tmp);
				}
				if (it % 5 != 0)  //向左移动
				{
					tmp.first = it;
					tmp.second = it - 1;
					allMove.push_back(tmp);
				}
				if (it > 4 && it % 5 != 0) //向左上移动
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
				if (it < 20)  //向下移动
				{
					tmp.first = it;
					tmp.second = it + 5;
					allMove.push_back(tmp);
				}
				if (it % 5 != 4)  //向右移动
				{
					tmp.first = it;
					tmp.second = it + 1;
					allMove.push_back(tmp);
				}
				if (it < 20 && it % 5 != 4) //向右下移动
				{
					tmp.first = it;
					tmp.second = it + 6;
					allMove.push_back(tmp);
				}
			}
			return;
		}
	}
	//根据该节点棋盘信息更新allMove（用于更新root节点）
	void handle(int &dice)  
	{
		allMove.clear();
		moveWay tmpMove;
		int j = 0; //可走子的个数
		int index[2]; //可下子的位置
		index[0] = -1, index[1] = -1;

		for (int i = 0; i < 25; ++i)
			if (curBoard[i] == dice)  //与色子点数相同的棋子还在棋盘上
			{
				index[0] = i;
				j = 1;
				break;
			}
		if (j == 0)   //与色子点数相同的棋子不在棋盘上
		{
			j = 1;
			int mindis1 = 25, mindis2 = 25;
			int tmpdis1, tmpdis2;
			if (color == blue)
			{
				for (int i = 0; i < 25; ++i)
					if (curBoard[i]>dice)  //找到大于色子点数的与其最接近的棋子所在位置
					{
						tmpdis1 = curBoard[i] - dice;
						if (tmpdis1 < mindis1)
						{
							mindis1 = tmpdis1;
							index[0] = i;
						}
					}
					else if (curBoard[i]>6) //找到小于色子点数的与其最接近的棋子所在位置
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
					if (curBoard[i] <= 6 && curBoard[i]>dice)  //找到大于色子点数的与其最接近的棋子所在位置
					{
						tmpdis1 = curBoard[i] - dice;
						if (tmpdis1 < mindis1)
						{
							mindis1 = tmpdis1;
							index[0] = i;
						}
					}
					else if (curBoard[i]>0 && curBoard[i] < dice) //找到小于色子点数的与其最接近的棋子所在位置
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
		if (color == blue)//对可移动棋子进行处理，得到可移动方向
			for (int k = 0; k < j; ++k)
			{
				if (index[k] > 4)  //向上
				{
					tmpMove.first = index[k];
					tmpMove.second = index[k] - 5;
					allMove.push_back(tmpMove);
				}
				if (index[k] % 5 != 0)  //向左
				{
					tmpMove.first = index[k];
					tmpMove.second = index[k] - 1;
					allMove.push_back(tmpMove);
				}
				if (index[k] > 4 && index[k] % 5 != 0)  //向左上
				{
					tmpMove.first = index[k];
					tmpMove.second = index[k] - 6;
					allMove.push_back(tmpMove);
				}
			}
		else for (int k = 0; k < j; ++k)
		{
			if (index[k] < 20)  //向下
			{
				tmpMove.first = index[k];
				tmpMove.second = index[k] + 5;
				allMove.push_back(tmpMove);
			}
			if (index[k] % 5 != 4)  //向右
			{
				tmpMove.first = index[k];
				tmpMove.second = index[k] + 1;
				allMove.push_back(tmpMove);
			}
			if (index[k] < 20 && index[k] % 5 != 4)  //向右下
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
	Node *root; //根节点,即当前面对棋局

public:
	bool color; //我方颜色
	Node *init; //开局节点
	Tree() { root = NULL; }

	string UCTSearch(int a[], int n, int dice);  //返回策略

	Node *treePolicy();   //树策略，返回用于模拟的节点（可扩展节点or最佳子节点）
	Node *expand(Node *p); //选择还未遍历的局面，作为新扩展的节点返回
	Node *bestChild(Node *p, double c = 1.96); //根据UCB公式选择p节点下的最佳子节点
											   /*参数c需要吗？？？*/

	bool rolloutPolicy(Node *p);  //模拟，随机走完一局棋，并返回结果
	void backUp(Node *p, bool result);  //回溯，更新根节点到p节点这一路径所有节点的胜率信息

	void moveByOpponent(int a[], int n, int dice);  //对方走子后更新根节点
												
}uct;

string Tree::UCTSearch(int a[], int n, int dice)
{
	time_t init, now;
	init = clock();

	moveByOpponent(a, 25, dice);//更新根节点

	//int coo = 1;

	now = clock();//(double)(t2 - t1)/ CLOCKS_PER_SEC * 1000
	while (((double)(now - init) / CLOCKS_PER_SEC) < 4.75)//未超时
	{
		//把多个步骤合在一起???
		//cout << "第" << coo << "次搜索" << endl;
		Node *simulate = treePolicy();
		//cout << "第" << coo << "次treePolicy完成" << endl;
		bool result = rolloutPolicy(simulate);
		//cout << "第" << coo << "次rolloutPolicy完成" << endl;
		backUp(simulate, result);
		//cout << "第" << coo << "次backUp完成" << endl;
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

	int p[2];  //最佳走子的棋子位置
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
	root = best; //我方走子后更新根节点
	
	return ans;
}

Node *Tree::treePolicy()
{
	Node *presentNode = root;
	while (!isWin(presentNode->curBoard, 25, !presentNode->color))//节点不是终止节点
	{
		if (presentNode->child.size() != presentNode->allMove.size()) //该节点可扩展
			return expand(presentNode);  //扩展该节点
		else presentNode = bestChild(presentNode);
	}
	return presentNode;
}

Node *Tree::expand(Node *p) //扩展节点p，并将扩展的节点加到p的子节点中，返回扩展的节点
{
	vector<moveWay> vaildMove;  //未遍历的走子方式
	Node *expandNode;
	bool flag;
	for (auto it : p->allMove)
	{
		flag = false;  //某一移动方式是否已经模拟
		for (auto itt : p->child)
			if (itt->moveway == it)
			{
				flag = true;
				break;
			}
		if (!flag)  //该方式未模拟
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
	if (init == NULL) //刚开局
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

		if (i == 25)  //对手下的棋我方已经模拟过
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

	//对手下的棋我方未模拟过
	Node *p = new Node(!color);
	p->father = root;
	for (int i = 0; i < 25; ++i)
		p->curBoard[i] = a[i];
	p->handle(dice);
	root = p;
}

void Tree::backUp(Node *p, bool result)
{
	while (p != root)  //是不是还可以==root???
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
	bool whoseTurn = p->color;  //轮到谁下
	int board[25];
	for (int i = 0; i < 25; ++i)
		board[i] = p->curBoard[i];
	while (!isWin(board, 25, !whoseTurn))  //未决出胜负
	{
		int dice = 1 + rand() % 6; //色子点数
		if (whoseTurn == blue)
			dice += 6;
		randMove(board, 25, dice, whoseTurn);
		whoseTurn = !whoseTurn;
	}
	if (isWin(board, 25, !whoseTurn) == 1)  //红方胜
		return red;
	else return blue;  //蓝方胜
}

Node *Tree::bestChild(Node *p, double c)
{
	//c = 1.96;//待修改

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
	if (s == "close")return -1;  //三局结束，退出游戏
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

	if (parse(clientsocket.getRecvMsg()) == -1)  //解析信息，更新棋盘
	{
		if (!IamWin)
			logging("Result: OpponentWin");
		return 0;
	}
	uct.color = mycolor;
	IamWin = false;

	//刚开局第一步不需要检查，此时checkOrNot为false
	if (checkOrNot)   //检查对方是否获胜导致重新开局
		if (check(chessboard, 25)) //确实重新开局,我方输掉一局
		{
			logging("Result: OpponentWin");
			uct.init = NULL;
			checkOrNot = false;
		}

	//策略函数
	string ans = uct.UCTSearch(chessboard, 25, dice);

	//logging(ans);  //将对战记录输出到终端并存到list容器中

	clientsocket.sendMsg(ans.c_str());  //发送信息，给出行动

	logging(ans);  //将对战记录输出到终端并存到list容器中

	updateBoard(chessboard, 25);

	if (isWin(chessboard, 25, mycolor) != 0) {
		checkOrNot = false;  //我方获胜会记录下来，故新开局无需检查
		IamWin = true;
		logging("Result: YouWin");
		uct.init = NULL;
	}
	else checkOrNot = true;  //从第二步棋开始检查

	for (int i = 0; i < 25; ++i)  //记录当前棋盘
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
