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
using namespace std;

int cnt = 0; //������3�ֽ���
bool checkOrNot = false; //�Ƿ�����ַ����ܴ�仯
int toCheck[25];  //��¼��һ����������̣����ڶԱȼ���Ƿ��¿���

bool color;//��¼�ҷ���ɫ��0Ϊ�죬1Ϊ�� 

inline void updateBoard(int chessboard[], int n, int index, string moveDir) //�������
{
	/*���Ż�*/

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
	int diff = 0;//ͳ��0�ĸ���
	for (int i = 0; i < 25; ++i)
		if (chessboard[i] != toCheck[i])diff++;
	if (diff > 2)return true;
	else return false;
}

int isWin(int chessboard[], int n)  //�ж�ĳ���Ƿ�ȡʤ
{

	//����ʤ2���췽ʤ1��δ����0

	//�ҷ�Ϊ��ɫ
	if (color) 
	{
		if (chessboard[0] > 6)return 2; //�ߵ��췽�������ǵ�
		int num = 0; //�췽ʣ��
		for (int i = 0; i < 25; ++i)
			if (chessboard[i] <= 6)num++;
		if (num == 0)return 2;
		return 0;
	}
	//�ҷ�Ϊ��ɫ
	else {
		if (chessboard[24] <= 6)return 1; //�ߵ������������ǵ�
		int num = 0; //����ʣ��
		for (int i = 0; i < 25; ++i)
			if (chessboard[i] > 6)num++;
		if (num == 0)return 1;
		return 0;
	}
}

string moveBlue(int chessboard[], int n, int index)  //��������ƶ�����
{
	/*���ȶԽ��߲��ԣ�������
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

int findBlueChess(int chessboard[], int n, int &dice)  //�ҵ������ӵ�λ��
{
	/*�ò��Ե�ǰֻ�ҵ���dice������С�����е�����С�ģ������������������
	��diceΪ3���ҷ���2��4������2�������������λ�ã�������
	*/

	pair<int, int> tmp; //��2��������ʾλ�ã���1��������ʾ��dice�Ĳ�ֵ
	vector<pair<int, int>> dis;  //�ҷ�������������Ĳ��
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
vector<int> findRedChess(int chessboard[], int n, int &dice)  //�ҵ������ӵ�λ��
{
	//���޸�

	vector<int> dis;  //�ҷ�������������Ĳ��
	vector<int> choice; //���µ�����
	for (int i = 0; i < 25; ++i)
		if (chessboard[i] <= 6)
			dis.push_back(abs(chessboard[i] - dice));
	int min = *min_element(dis.begin(), dis.end());
	for (auto it : dis)
		if (it == min)choice.push_back(it);
	return choice;
}

string silly(int chessboard[], int n, int &dice)  //������Ӳ��������
{
	int index;
	if (color)//�ҷ�Ϊ��ɫ
	{
		index = findBlueChess(chessboard, n, dice); //Ҫ�ߵ��ӵ�λ��
		stringstream ss;
		ss << chessboard[index];
		string ch; 
		ss >> ch;  //Ҫ�ߵ��ӵĵ���
		string moveDir= moveBlue(chessboard, n, index); //���ӷ���

		//�������
		updateBoard(chessboard, 25, index, moveDir);

		return ch + '|' + moveDir;
	}
	//�ҷ�Ϊ��ɫ
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
		color = 1;
	else color = 0;
	return 0;
}

int Einstein::handle()
{
	clientsocket.recvMsg();

	if (parse(clientsocket.getRecvMsg()) == -1)  //������Ϣ����������
	{
		logging("Result: RedWin");
		return 0;
	}

	//�տ��ֵ�һ������Ҫ��飬��ʱcheckOrNotΪfalse
	if (checkOrNot)   //���Է��Ƿ��ʤ�������¿���
		if (check(chessboard, 25)) //ȷʵ���¿���,�ҷ����һ��
		{
			cnt++;
			logging("Result: RedWin");
		}

	//���Ժ���
	string ans = silly(chessboard, 25, dice);

	logging(ans);  //����ս��¼������ն˲��浽list������

	clientsocket.sendMsg(ans.c_str());  //������Ϣ�������ж�

	if (isWin(chessboard, 25) != 0) {
		cnt++;  //�ҷ�Ӯ��һ��
		checkOrNot = false;  //�ҷ���ʤ���¼���������¿���������
		logging("Result: BlueWin");
	}
	else checkOrNot = true;  //�ӵڶ����忪ʼ���
	if (cnt == 3)return 0;

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

	if (s[0] == 'd')
	{
		s = ": " + s;
		s = c + s + '\n';
		cout << s;
		logger.push_back(s);
		return 0;
	}

	if (s[0] == 'R')
	{
		list<string>::iterator it = logger.end();
		for (it--; it != logger.begin() && (*it)[21] != 'R'; --it);
		if (it != logger.begin())
			++it;

		int day1, hour1, minute1, second1;
		stringstream ss[8];
		ss[0] << (*it)[8] << (*it)[9];
		ss[0] >> day1;
		ss[1] << (*it)[11] << (*it)[12];
		ss[1] >> hour1;
		ss[2] << (*it)[14] << (*it)[15];
		ss[2] >> minute1;
		ss[3] << (*it)[17] << (*it)[18];
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
	for (auto it = p.begin(); *it != '|'; ++it)
		tmp.push_back(*it);

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
	ofstream fout(filename);
	for (; it != logger.end(); ++it)
		fout << *it;
	fout.close();
	return 0;
}
