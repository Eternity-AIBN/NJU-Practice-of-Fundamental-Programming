#include"lexical.h"
#include"grammar.h"

void Lexical::handle()
{
	for (auto &it : tokenTable)
	{
		/*for (auto &p : it) //remove the black space
		{
			while (p.first.front() == ' ')
				p.first.erase(p.first.begin());
			while (p.first.back() == ' ')
				p.first.erase(p.first.end()-1);
		}*/
		if (it.first.front().first[0] == '/'&&it.first.front().first[1] == '*')  //It is annotation.
			it.first.front().second = "annotation";
		else {
			for (auto &p : it.first)
				if (p.first == ")" || p.first == "(" || p.first == "," || p.first[0] == ':' || p.first[0] == '.')
					p.second = "symbol";
				else if (isupper(p.first[0]))
					p.second = "variable";
				else if (islower(p.first[0]))
					p.second = "atom";
		}
	}
}

void Grammar::handleFact()
{
	for (auto it : lex.tokenTable)
		if (!it.second)
		{
			Fact tmp;
			tmp.name = it.first[0].first;
			unsigned int i = 2;
			for (; i < it.first.size(); ++i)
				if (it.first[i].second != "symbol")
					tmp.relation.push_back(it.first[i].first);
			allFacts.push_back(tmp);
		}
}

void Grammar::handleRule()
{
	for (auto it : lex.tokenTable)
		if (it.second)
		{
			Rule tmpRule;
			tmpRule.name = it.first[0].first;
			unsigned int i = 2;
			for (; it.first[i].first != ")"; ++i)
				if (it.first[i].second != "symbol")
					tmpRule.arguements.push_back(it.first[i].first);

			while (i < it.first.size() - 2)
			{
				i += 2;
				Fact tmpFact;
				tmpFact.name = it.first[i].first;
				for (i += 2; it.first[i].first != ")"; ++i)
					if (it.first[i].second != "symbol")
						tmpFact.relation.push_back(it.first[i].first);
				tmpRule.def.push_back(tmpFact);
			}

			allRules.push_back(tmpRule);
		}
}