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
		for (auto p : it)
		{
			if (p.second == "atom")
			{
				for (auto tmp : p.first)
					if (tmp != '_' && !isalnum(tmp))
					{
						tmpError.second = "The atom can only contains '_',letter and number.";
						allErrors.push_back(tmpError);
						break;
					}
			}
			else if (p.second == "variable")
			{
				for (auto tmp : p.first)
					if (tmp != '_' && !isalnum(tmp))
					{
						tmpError.second = "The variable can only contains '_',letter and number.";
						allErrors.push_back(tmpError);
						break;
					}
			}
			else if (p.second == "annotation")
				if (*(p.first.end() - 1) != '/' || *(p.first.end() - 2) != '*')
				{
					tmpError.second = "The annotation is wrong.";
					allErrors.push_back(tmpError);
					break;
				}
		}
	}
	if (allErrors.size() != 0)
		for (auto it : allErrors)
			cout << "Line " << it.first << ": " << it.second << endl;
}

void Grammar::checkError()
{

}