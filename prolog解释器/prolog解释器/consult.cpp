#include"grammar.h"

bool Grammar::judgeFact(Fact tmpFact)
{
	auto it = allFacts.begin();
	for (; it != allFacts.end(); ++it)
		if (it->name == tmpFact.name&&it->relation.size() == tmpFact.relation.size())
		{
			unsigned int j = 0;
			for (; j < tmpFact.relation.size(); ++j)
				if (tmpFact.relation[j] != it->relation[j]) break;
			if (j == tmpFact.relation.size())
				return true;
		}
	return false;
}

vector<string> Grammar::findTheAns(Fact tmpFact,string anotherVariable)
{
	vector<string> anss;
	string ss;
	auto it = allFacts.begin();
	for (; it != allFacts.end(); ++it)
		if (it->name == tmpFact.name&&it->relation.size() == tmpFact.relation.size())
		{
			unsigned int j = 0;
			for (; j < tmpFact.relation.size(); ++j)
			{
				if (tmpFact.relation[j] != anotherVariable) //It is an atom
				{
					if (tmpFact.relation[j] != it->relation[j])break;
				}
				else ss = it->relation[j];
			}
			if(j== tmpFact.relation.size())
				anss.push_back(ss);
		}
	return anss;
}

void Grammar::consultFact(string cmd)
{
	Fact tmp;
	string s;
	unsigned int i = 0;
	for (; cmd[i] != '('; ++i)
		tmp.name += cmd[i];
	++i;
	for (; cmd[i] != ')'; ++i)
	{
		if (cmd[i] != ',')
			s += cmd[i];
		else { 
			tmp.relation.push_back(s);
			s.clear();
		}
	}
	tmp.relation.push_back(s);

	vector<int> variableLocate;
	for (unsigned int k = 0; k < tmp.relation.size(); ++k)
		if (isupper(tmp.relation[k].front()))
			variableLocate.push_back(k);

	if (variableLocate.size() == 0)  //Confirmatory statement
	{
		if(judgeFact(tmp))
			cout << "true." << endl << endl;
		else cout << "false." << endl << endl;
		return;
	}
	else {   //Query statement
		allAns.clear();
		auto it = allFacts.begin();
		for (; it != allFacts.end(); ++it)
			if (it->name == tmp.name&&it->relation.size()==tmp.relation.size())
			{
				oneAns OAns;
				unsigned int j = 0, h = 0;
				for (; j < tmp.relation.size(); ++j)
				{
					if (h >= variableLocate.size() || j != variableLocate[h]) //It is an atom
					{
						if (tmp.relation[j] != it->relation[j])break;
					}
					else {  //It is a variable
						partOfAns pAns(tmp.relation[j], it->relation[j]);
						h++;
						OAns.push_back(pAns);
					}
				}
				if (!OAns.empty())
					allAns.push_back(OAns);
			}
		if (allAns.empty())
			cout << "false" << endl;
		else for (auto p = allAns.begin(); p != allAns.end(); ++p)
		{
			for (auto pp : *p)
				cout << pp.first << " = " << pp.second << '\t';
			cout << endl;
		}
		cout << endl;
	}
}

bool Grammar::conRule0(Rule tmprule, Fact tmpfact)
{
	unsigned int i = 0;
	for (; i < tmprule.arguements.size(); ++i)   
		if (tmprule.arguements[i] != tmpfact.relation[i]) //The arguements do not match.
			return false;

	for (auto p : tmprule.def)
	{
		if (!judgeFact(p))
			return false;
	}
	return true;
}
bool Grammar::conRule1(Rule tmprule, Fact tmpfact)
{
	string theVariable, theAtom;
	unsigned int i = 0;
	for (; i < tmprule.arguements.size(); ++i)
		if (tmprule.arguements[i] != tmpfact.relation[i]) //The arguements do not match.
		{
			if (isupper(tmprule.arguements[i].front()))
			{
				theVariable = tmprule.arguements[i];
				theAtom = tmpfact.relation[i];
			}
			else return false;
		}

	for (auto it : tmprule.def)
	{
		for (unsigned int j = 0; j < it.relation.size();++j)
			if (it.relation[j] == theVariable)   //做变量替换
				it.relation[j] = theAtom;
		if (!judgeFact(it))return false;
	}
	return true;
}
bool Grammar::conRule2(Rule tmprule, Fact tmpfact)
{
	string theVariable[2], theAtom[2];
	unsigned int i = 0, k = 0;
	for (; i < tmprule.arguements.size(); ++i)
		if (tmprule.arguements[i] != tmpfact.relation[i]) //The arguements do not match.
		{
			if (isupper(tmprule.arguements[i].front()) && k < 2)
			{
				theVariable[k] = tmprule.arguements[i];
				theAtom[k] = tmpfact.relation[i];
				k++;
			}
			else return false;
		}

	for (unsigned int aa = 0; aa < tmprule.def.size();++aa)
	{
		for (unsigned int j = 0; j < tmprule.def[aa].relation.size(); ++j)
			if (tmprule.def[aa].relation[j] == theVariable[0])   //变量替换
				tmprule.def[aa].relation[j] = theAtom[0];
			else if (tmprule.def[aa].relation[j] == theVariable[1])   //变量替换
				tmprule.def[aa].relation[j] = theAtom[1];
	}
	bool flag = false; //标记变量替换后fact中还有没有变量
	string anotherVariable;  //未被替换的变量
	for (auto it : tmprule.def)
	{
		for (auto p : it.relation)
			if (isupper(p.front()))
			{
				flag = true; 
				anotherVariable = p;
				break;
			}
	}
	if (!flag)
	{
		for (auto p : tmprule.def)
		{
			if (!judgeFact(p))
				return false;
		}
		return true;
	}
	else {
		vector<string> ans = findTheAns(tmprule.def.front(), anotherVariable);
		for (unsigned int kk = 0; kk < ans.size();++kk)
		{
			if(kk==0)
				for (unsigned int aa = 0; aa < tmprule.def.size(); ++aa)
				{
					for (unsigned int j = 0; j < tmprule.def[aa].relation.size(); ++j)
						if (tmprule.def[aa].relation[j] == anotherVariable)   //变量替换
							tmprule.def[aa].relation[j] = ans[kk];
				}
			else {
				for (unsigned int aa = 0; aa < tmprule.def.size(); ++aa)
				{
					for (unsigned int j = 0; j < tmprule.def[aa].relation.size(); ++j)
						if (tmprule.def[aa].relation[j] == ans[kk - 1])   //变量替换
							tmprule.def[aa].relation[j] = ans[kk];
				}
			}
			unsigned int ii = 0;
			for (; ii < tmprule.def.size(); ++ii)
				if (!judgeFact(tmprule.def[ii]))break;
			if (ii == tmprule.def.size())return true;
		}
		return false;
	}
}

void Grammar::consultRule(string cmd)
{
	Fact tmp;
	string s;
	unsigned int i = 0;
	for (; cmd[i] != '('; ++i)
		tmp.name += cmd[i];
	++i;
	for (; cmd[i] != ')'; ++i)
	{
		if (cmd[i] != ',')
			s += cmd[i];
		else {
			tmp.relation.push_back(s);
			s.clear();
		}
	}
	tmp.relation.push_back(s);

	string replaceAtom, replaceVar;  //对于grandfather(X,Y),输入...(john,Y)后replace为john
	vector<int> variableLocate;
	for (unsigned int k = 0; k < tmp.relation.size(); ++k)
	{
		if (isupper(tmp.relation[k].front()))
		{
			replaceVar = tmp.relation[k];
			variableLocate.push_back(k);
		}
		else replaceAtom = tmp.relation[k];
	}

	if (variableLocate.size() == 0)  //Confirmatory statement
	{
		auto it = allRules.begin();
		for (; it != allRules.end(); ++it)
			if (it->name == tmp.name&&it->arguements.size() == tmp.relation.size())
			{
				if (it->numOfVariable == 0 && conRule0(*it, tmp))
				{
					cout << "true." << endl << endl;
					return;
				}
				else if (it->numOfVariable == 1 && conRule1(*it, tmp))
				{
					cout << "true." << endl << endl;
					return;
				}
				else if (it->numOfVariable == 2 && conRule2(*it, tmp))
				{
					cout << "true." << endl << endl;
					return;
				}
			}
		cout << "false." << endl << endl;
	}
	else {   //Query statement
		allAns.clear();
		if (variableLocate.size() == 1) //一个变量的查询
		{
			for (auto it : allRules)
			{
				if (it.name == tmp.name&&it.arguements.size() == tmp.relation.size())
				{
					unsigned int i2 = 0;
					for (; i2 < it.arguements.size(); ++i2)
						if (!isupper(it.arguements[i2].front()) && it.arguements[i2] != replaceAtom)
							break;
					if (i2 != it.arguements.size())continue;

					string theAtom, theVar;
					for (unsigned int jj = 0; jj < it.arguements.size(); ++jj)
						if (jj != variableLocate.front())
							theAtom = it.arguements[jj]; //把变量替换成原子
						else theVar = it.arguements[jj];  //把变量替换成另一个变量名
						for (auto pp = it.def.begin(); pp != it.def.end(); ++pp)  //变量替换
						{
							for (unsigned int jj = 0; jj < pp->relation.size(); ++jj)
								if (pp->relation[jj] == theAtom)
									pp->relation[jj] = replaceAtom;
								else if (pp->relation[jj] == theVar)
									pp->relation[jj] = replaceVar;
						}

						//对于只有一个参数的fact替换后不存在变量，检查其是否正确
						bool flag2 = false;
						auto pp2 = it.def.begin();
						for (; pp2 != it.def.end(); ++pp2)
						{
							if (pp2->relation.size() == 1)
								if (isupper(pp2->relation[0].front()))
									flag2 = true;
								else if (!judgeFact(*pp2))break;
								else flag2 = true;
								if (pp2 != it.def.end()) continue;
						}

						int vnum = 0;
						auto it3 = it.def.begin();
						for (; it3 != it.def.end(); ++it3) //找到替换后只含有一个变量的fact
						{
							for (auto p : it3->relation)
								if (isupper(p.front()))vnum++;
							if (vnum == 1)break;
							else vnum = 0;
						}

						string anotherVariable;  //上述fact中未被替换的变量
						for (auto p : it3->relation)
							if (isupper(p.front()))
							{
								anotherVariable = p;
								break;
							}

						vector<string> ans = findTheAns(*it3, anotherVariable);
						for (unsigned int kk = 0; kk < ans.size(); ++kk)
						{
							if (kk == 0)
								for (unsigned int aa = 0; aa < it.def.size(); ++aa)
								{
									for (unsigned int j = 0; j < it.def[aa].relation.size(); ++j)
										if (it.def[aa].relation[j] == anotherVariable)   //变量替换
											it.def[aa].relation[j] = ans[kk];
								}
							else {
								for (unsigned int aa = 0; aa < it.def.size(); ++aa)
								{
									for (unsigned int j = 0; j < it.def[aa].relation.size(); ++j)
										if (it.def[aa].relation[j] == ans[kk - 1])   //变量替换
											it.def[aa].relation[j] = ans[kk];
								}
							}
							if (it.numOfVariable == 1 || flag2)
							{
								unsigned int ii = 0;
								for (; ii < it.def.size(); ++ii)
									if (!judgeFact(it.def[ii]))break;
								if (ii == it.def.size())
								{
									partOfAns pAns(anotherVariable, ans[kk]);
									oneAns oAns;
									oAns.push_back(pAns);
									allAns.push_back(oAns);
								}
							}
							else if (it.numOfVariable == 2)
							{
								string tss;
								Fact tf;
								auto it4 = it.def.begin();
								for (; it4 != it.def.end(); ++it4) //找到替换后剩下的最后一个变量
								{
									for (auto p : it4->relation)
										if (isupper(p.front())) { tss = p; tf = *it4; break; }
								}

								vector<string> ans2 = findTheAns(tf, tss);

								for (unsigned int kkk = 0; kkk < ans2.size(); ++kkk)
								{
									partOfAns pAns(tss, ans2[kkk]);
									oneAns oAns;
									oAns.push_back(pAns);
									allAns.push_back(oAns);
								}
							}
						}
				}
			}
		}
		else if (variableLocate.size() == 2)
		{
			string replaceVar1, replaceVar2;
			replaceVar1 = tmp.relation[variableLocate[0]];
			replaceVar2 = tmp.relation[variableLocate[1]];
			for (auto it : allRules)
			{
				if (it.name == tmp.name&&it.arguements.size() == tmp.relation.size())
					if (isupper(it.arguements[0].front()) && isupper(it.arguements[1].front()))//两个参数都是变量
					{
						bool flag2 = true; //判断rule中是否只存在两个变量
						for (unsigned int i2 = 0; i2 < it.def.size(); ++i2)    //变量名替换
						{
							for (unsigned int j2 = 0; j2 < it.def[i2].relation.size(); ++j2)
								if (it.def[i2].relation[j2] == it.arguements[0])
									it.def[i2].relation[j2] = replaceVar1;
								else if (it.def[i2].relation[j2] == it.arguements[1])
									it.def[i2].relation[j2] = replaceVar2;
								else flag2 = false;
						}
						if (flag2) //只有两个变量
						{
							auto aim = it.def.begin();
							for (; aim != it.def.end(); ++aim) //找到有两个参数的fact
								if (aim->relation.size() >= 2)break;
							vector<pair<string, string>> mayBeAns; //找到可能的答案，两个参数分别表示两个变量
							for (auto it2 : allFacts)
							{
								if (it2.name == aim->name&&it2.relation.size() == aim->relation.size())
								{
									pair<string, string> tmpAns;
									if (it2.relation[0] == replaceVar1)
										tmpAns.first = it2.relation[0], tmpAns.second = it2.relation[1];
									else tmpAns.first = it2.relation[1], tmpAns.second = it2.relation[0];
									mayBeAns.push_back(tmpAns);
								}
							}

							for (auto it2 : mayBeAns)
							{
								bool judgeFlag = true; //判断某一组答案是否正确
								for (auto it3 : it.def)
									if (it3.relation.size() == 1)
									{
										if (it3.relation[0] == replaceVar1)
											it3.relation[0] = it2.first;
										else if (it3.relation[0] == replaceVar2)
											it3.relation[0] = it2.second;
										if (!judgeFact(it3)) {
											judgeFlag = false;
											break;
										}
									}
								if (judgeFlag) //答案正确
								{
									partOfAns pAns1(replaceVar1, it2.first);
									partOfAns pAns2(replaceVar2, it2.second);
									oneAns oAns;
									oAns.push_back(pAns1);
									oAns.push_back(pAns2);
									allAns.push_back(oAns);
								}
							}
						}
						else { //存在第三个变量
							string anotherVar; //第三个变量
							for (auto itt : it.def.front().relation)
								if (itt != replaceVar1&&itt != replaceVar2)
									anotherVar = itt;

							vector<pair<string, string>> mayBeAns1, mayBeAns2;
							//根据两个fact找到可能的答案，第一个参数表示第三个变量
							for (auto it2 : allFacts)
							{
								if (it2.name == it.def[0].name&&it2.relation.size() == it.def[0].relation.size())
								{
									pair<string, string> tmpAns;
									if (it.def[0].relation[0] == anotherVar)
										tmpAns.first = it2.relation[0], tmpAns.second = it2.relation[1];
									else tmpAns.first = it2.relation[1], tmpAns.second = it2.relation[0];
									mayBeAns1.push_back(tmpAns);
								}
								if (it2.name == it.def[1].name&&it2.relation.size() == it.def[1].relation.size())
								{
									pair<string, string> tmpAns;
									if (it.def[1].relation[0] == anotherVar)
										tmpAns.first = it2.relation[0], tmpAns.second = it2.relation[1];
									else tmpAns.first = it2.relation[1], tmpAns.second = it2.relation[0];
									mayBeAns2.push_back(tmpAns);
								}
							}

							for (auto it2 : mayBeAns1)
								for (auto itt2 : mayBeAns2)
									if (it2.first == itt2.first)
									{
										if (it.def[0].relation[0] == replaceVar1 || it.def[0].relation[1] == replaceVar1)
										{
											partOfAns pAns1(replaceVar1, it2.second);
											partOfAns pAns2(replaceVar2, itt2.second);
											oneAns oAns;
											oAns.push_back(pAns1);
											oAns.push_back(pAns2);
											allAns.push_back(oAns);
										}
										else {
											partOfAns pAns1(replaceVar2, it2.second);
											partOfAns pAns2(replaceVar1, itt2.second);
											oneAns oAns;
											oAns.push_back(pAns2);
											oAns.push_back(pAns1);
											allAns.push_back(oAns);
										}
									}
						}
					}
			}
		}
	}

	if (allAns.empty())
		cout << "false." << endl;
	else for (auto p = allAns.begin(); p != allAns.end(); ++p)
	{
		for (auto pp : *p)
			cout << pp.first << " = " << pp.second << '\t';
		cout << endl;
	}
	cout << endl;
}