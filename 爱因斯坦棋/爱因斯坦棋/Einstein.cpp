#define _CRT_SECURE_NO_WARNINGS
#include "Einstein.h"
#include<iostream>
#include<cctype>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<sstream>
using namespace std;

int cnt = 0; //局数，3局结束
bool checkOrNot = false; //是否检查棋局发生很大变化
int toCheck[25];  //记录上一步下完的棋盘，用于对比检查是否新开局

bool color;//记录我方颜色，0为红，1为蓝 

inline void updateBoard(int chessboard[], int n, int index, string moveDir) //更新棋局
{
	/*待优化*/

	if (moveDir == "up")
		chessboard[index - 5] = chessboard[index];
	else if(moveDir == "left")
		chessboard[index - 1] = chessboard[index];
	else if (moveDir == "leftup")
		chessboard[index - 6] = chessboard[index];
	else if (moveDir == "down")
		chessboard[index + 5] = chessboard[index];
	else if (moveDir == "right")
		chessboard[index + 1] = chessboard[index];
	else if (moveDir == "rightdown")
		chessboard[index + 6] = chessboard[index];
	chessboard[index] = 0;
}

inline bool check(int chessboard[], int n)
{
	int diff = 0;//统计0的个数
	for (int i = 0; i < 25; ++i)
		if (chessboard[i] != toCheck[i])diff++;
	if (diff > 2)return true;
	else return false;
}

int isWin(int chessboard[], int n)  //判断某方是否取胜
{

	//蓝方胜2，红方胜1，未结束0

	//我方为蓝色
	if (color) 
	{
		if (chessboard[0] > 6)return 2; //走到红方出发区角点
		int num = 0; //红方剩子
		for (int i = 0; i < 25; ++i)
			if (chessboard[i] <= 6)num++;
		if (num == 0)return 2;
		return 0;
	}
	//我方为红色
	else {
		if (chessboard[24] <= 6)return 1; //走到蓝方出发区角点
		int num = 0; //蓝方剩子
		for (int i = 0; i < 25; ++i)
			if (chessboard[i] > 6)num++;
		if (num == 0)return 1;
		return 0;
	}
}

string moveBlue(int chessboard[], int n, int index)  //蓝棋随机移动策略
{
	/*优先对角线策略，待完善
	*/
	vector<string> ways;
	if (index > 4)
		ways.push_back("up");
	if (index %5!=0)
		ways.push_back("left");
	if (ways.size() == 2)
		return "leftup";
	int i = rand() % ways.size();
	return ways[i];
}

int findBlueChess(int chessboard[], int n, int &dice)  //找到可下子的位置
{
	/*该策略当前只找到与dice距离最小的子中点数最小的，还不够随机，待完善
	如dice为3，我方有2和4，返回2这个点数（所在位置！！！）
	*/

	pair<int, int> tmp; //第2个参数表示位置，第1个参数表示与dice的差值
	vector<pair<int, int>> dis;  //我方所有棋与点数的差距
	for (int i = 0; i < 25; ++i)
		if (chessboard[i]>6)
		{
			tmp.first = abs(chessboard[i] - dice);
			tmp.second = i;
			dis.push_back(tmp);
		}
	pair<int,int> min = *min_element(dis.begin(), dis.end());
	return min.second;
}
vector<int> findRedChess(int chessboard[], int n, int &dice)  //找到可下子的位置
{
	//待修改

	vector<int> dis;  //我方所有棋与点数的差距
	vector<int> choice; //可下的棋子
	for (int i = 0; i < 25; ++i)
		if (chessboard[i] <= 6)
			dis.push_back(abs(chessboard[i] - dice));
	int min = *min_element(dis.begin(), dis.end());
	for (auto it : dis)
		if (it == min)choice.push_back(it);
	return choice;
}

string silly(int chessboard[], int n, int &dice)  //随机走子并更新棋局
{
	int index;
	if (color)//我方为蓝色
	{
		index = findBlueChess(chessboard, n, dice); //要走的子的位置
		stringstream ss;
		ss << chessboard[index];
		string ch; 
		ss >> ch;  //要走的子的点数
		string moveDir= moveBlue(chessboard, n, index); //走子方向

		//更新棋局
		updateBoard(chessboard, 25, index, moveDir);

		return ch + '|' + moveDir;
	}
	//我方为红色
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
		color = 1;
	else color = 0;
	return 0;
}

int Einstein::handle()
{
	clientsocket.recvMsg();

	if (parse(clientsocket.getRecvMsg()) == -1)  //解析信息，更新棋盘
		return 0;

	//刚开局第一步不需要检查，此时checkOrNot为false
	if (checkOrNot)   //检查对方是否获胜导致重新开局
		if (check(chessboard, 25)) //确实重新开局,我方输掉一局
		{
			cnt++;
			cout << "第" << cnt << "局结束，对方获胜" << endl;
		}

	//策略函数
	string ans = silly(chessboard, 25, dice);

	logging(ans);  //将对战记录输出到终端并存到list容器中

	clientsocket.sendMsg(ans.c_str());  //发送信息，给出行动

	if (isWin(chessboard, 25) != 0) {
		cnt++;  //我方赢得一局
		checkOrNot = false;  //我方获胜会记录下来，故新开局无需检查
		cout << "第" << cnt << "局结束，你获胜" << endl;
	}
	else checkOrNot = true;  //从第二步棋开始检查
	if (cnt == 3)return 0;

	for (int i = 0; i < 25; ++i)  //记录当前棋盘
		toCheck[i] = chessboard[i];

	return 1;
}

int Einstein::logging(std::string s)
{
	string tmp = " ：";
	string p = clientsocket.getRecvMsg();
	for (auto it = p.begin(); *it != '|'; ++it)
		tmp.push_back(*it);


	char c[64];
	time_t timep;
	time(&timep);
	strftime(c, sizeof(c), "%Y-%m-%d %H-%M-%S", localtime(&timep));

	tmp += " ||chess&move：" + s;
	tmp = c + tmp;

	cout << tmp << endl;
	logger.push_back(tmp);
	return 0;
}

int Einstein::writelog()
{
	return 0;
}
