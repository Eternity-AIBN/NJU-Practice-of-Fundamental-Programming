#include"lexical.h"
#include"grammar.h"
#include<cctype>

void Lexical::checkError()
{
	int numOfLine = 0;
	for (auto it : tokenTable)
	{
		numOfLine++;
		ErrorAndLine tmpError;
		tmpError.first = numOfLine;
		for (auto p : it.first)
		{
			if (p.second == "atom")
			{
				for (auto tmp : p.first)
					if (tmp != '_' && !isalnum(tmp))
					{
						tmpError.second.push_back("The atom can only contains '_',letter and number.");
						allErrors.push_back(tmpError);
						break;
					}
			}
			else if (p.second == "variable")
			{
				for (auto tmp : p.first)
					if (tmp != '_' && !isalnum(tmp))
					{
						tmpError.second.push_back("The variable can only contains '_',letter and number.");
						allErrors.push_back(tmpError);
						break;
					}
			}
			else if (p.second == "annotation")
				if (*(p.first.end() - 1) != '/' || *(p.first.end() - 2) != '*')
				{
					tmpError.second.push_back("The annotation is wrong.");
					allErrors.push_back(tmpError);
					break;
				}
		}
	}
	if (!allErrors.empty())
	{
		cout << "Lexical error!" << endl;
		for (auto it : allErrors)
			cout << "Line " << it.first << ": " << it.second[0] << endl;
	}
}

void Grammar::checkError()
{
	int numOfLine = 0;
	bool flag = false;  //To judge if there exist ":-"
	for (auto it : lex.tokenTable)
	{
		numOfLine++;
		ErrorAndLine tmpError;
		tmpError.first = numOfLine;

		if (it.first[0].second == "annotation")
		{
			if (it.first[0].first[it.first[0].first.size() - 2] != '*' || it.first[0].first[it.first[0].first.size() - 1] != '/')
			{
				tmpError.second.push_back("The annotation is wrong!");
				allErrors.push_back(tmpError);
			}
			continue;
		}

		if (it.first[1].first != "(")
		{
			if (it.second)
				tmpError.second.push_back("There is no parameter in the define of rule!");
			else tmpError.second.push_back("There is no parameter in the define of fact!");
		}

		if (it.first[it.first.size() - 1].first != ".")
			tmpError.second.push_back("There is no full stop(.) at the end of the sentence!");
		else if (it.first[it.first.size() - 2].first == ".")
			tmpError.second.push_back("There is more than one full stop(.) at the end of the sentence!");

		//To check the "(" and ")"
		int numOFparentheses = 0;
		for (auto p : it.first)
			if (p.first == "(")numOFparentheses++;
			else if (p.first == ")")
			{
				if (numOFparentheses == 1)
					numOFparentheses--;
				else { numOFparentheses = 1; break; }
			}
		if (numOFparentheses != 0)
			tmpError.second.push_back("The parentheses() are not matched!");

		//To check the ":-"
		for (auto p : it.first)
			if (p.first[0] == ':'&&p.first != ":-")
				tmpError.second.push_back("The symbol ':-' are wrong!");

		//To check if lack ","
		for (unsigned int i = 0; i < it.first.size() - 2; ++i)
			if ((it.first[i].second == "atom" || it.first[i].second == "variable" || it.first[i].first == ")") && (it.first[i + 1].second == "atom" || it.first[i + 1].second == "variable"))
			{
				tmpError.second.push_back("The comma is lacked!");
				break;
			}

		if (tmpError.second.empty() && !it.second)  //There is no error above, and it is a fact
		{
			for (unsigned int i = 2; i < it.first.size(); ++i)
				if (it.first[i].second != "symbol"&&it.first[i].second != "atom")
				{
					tmpError.second.push_back("The fact cannot contain variable!");
					break;
				}
		}

		allErrors.push_back(tmpError);
	}

	if (!allErrors.empty())
	{
		cout << "Grammar error!" << endl;
		for (auto it : allErrors)
			for (unsigned int i = 0; i < it.second.size(); ++i)
				cout << "Line " << it.first << ": " << it.second[i] << endl;
	}
	else   //To check the rule
	{
		handleFact();

		numOfLine = 0;
		for (auto it : lex.tokenTable)
		{
			numOfLine++;
			if (it.second)
			{
				ErrorAndLine tmpError;
				auto p = it.first.begin();
				for (; (*p).first != ":-"; ++p);

				while (1)
				{
					string factName = (*p).first;
					p++;
					if ((*p).first != "(")
					{
						tmpError.second.push_back("The fact lacks parameter!");
						break;
					}

					p++;
					int numOfParameter = 0;
					for (; (*p).first != ")"; ++p)
						if ((*p).second != "symbol")numOfParameter++;

					auto p2 = allFacts.begin();
					for (; p2 != allFacts.end(); ++p2)
						if (factName == p2->name&&p2->relation.size() == numOfParameter)
							break;
					if (p2 != allFacts.end())
					{
						tmpError.second.push_back("The fact has not define!");
						break;
					}
					p += 2;
					if (p == it.first.end())break;
				}
			}
		}
	}

	if (allErrors.empty())
		handleRule();
}