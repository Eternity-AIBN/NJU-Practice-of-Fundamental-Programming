#include"lexical.h"
#include"grammar.h"
#include<fstream>
#define FACT 0
#define RULE 1

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
	if (i == cmd.size() - 1)
		return true;
	else {
		cout << "Invalid command." << endl;
		return false;
	}
}

bool judgeCmd(string cmd)  //To judge the cmd is to consult a fact or a rule.
{ 
	string name;
	for (auto p = cmd.begin(); *p != '('; ++p)
		name += *p;
	for (auto it : lex.tokenTable)
	{
		if (it.first.front().first == name)
			if (it.second)return RULE;
			else return FACT;
	}
	return FACT;  //The fact/rule does not exist.Reguard it as a fact. 
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
	while (cmd!="halt.")
	{
		if (checkCMD(cmd))
		{
			if (judgeCmd(cmd) == FACT)
				consultFact(cmd);
			else consultRule(cmd);
			allAns.clear();
		}
		cout << "?- ";
		cin >> cmd;
	}
	return true;
}