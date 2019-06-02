#include"lexical.h"
#include"grammar.h"
#include<fstream>

bool checkCMD(string cmd)
{
	if (cmd.back() != '.')
	{
		cout << "Invalid command.(Lack of full stop)" << endl;
		return false;
	}
	unsigned int i = 0;
	for (; i < cmd.size(); ++i)
		if (cmd[i] == '(')break;
	for (; i < cmd.size(); ++i)
		if (cmd[i] == ')')break;
	if(i==cmd.size())
	{
		cout << "Invalid command.(The parentheses are wrong)" << endl;
		return false;
	}
	++i;
	if (i == cmd.size() - 1 && cmd[i] == '.')
		return true;
	else {
		cout << "Invalid command." << endl;
		return false;
	}
}

bool Lexical::run(string fname)
{
	if (!readInfo(fname))
		return false;
	handle();
	checkError();
	if (allErrors.size() != 0)
		return false;
	return true;
}

bool Grammar::run()
{
	checkError();
	if (allErrors.size() != 0)
		return false;
	cout << "true." << endl << endl;

	cout << "?- ";
	string cmd;
	cin >> cmd;
	while (cmd!="halt.") //Todo：修改退出循环的条件
	{
		if (checkCMD(cmd))
			consultFact(cmd);
		cout << "?- ";
		cin >> cmd;
	}
	return true;
}