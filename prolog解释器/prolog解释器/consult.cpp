#include"grammar.h"

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
		auto it = allFacts.begin();
		for (; it != allFacts.end(); ++it)
			if (it->name == tmp.name&&it->relation.size() == tmp.relation.size())
			{
				unsigned int j = 0;
				for (; j < tmp.relation.size(); ++j)
					if (tmp.relation[j] != it->relation[j])break;
				if (j == tmp.relation.size())
				{
					cout << "true." << endl << endl;
					return;
				}
			}
		cout << "false." << endl << endl;
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
		for (auto p = allAns.begin(); p != allAns.end(); ++p)
		{
			for (auto pp : *p)
				cout << pp.first << " = " << pp.second << '\t';
			cout << endl;
		}
		cout << endl;
	}
}