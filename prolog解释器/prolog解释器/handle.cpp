#include"lexical.h"
#include"grammar.h"
#include<cctype>

void Lexical::handle()
{
	for (auto &it : tokenTable)
	{
		for (auto &p : it) //remove the black space
		{
			while (p.first.front() == ' ')
				p.first.erase(p.first.begin());
			while (p.first.back() == ' ')
				p.first.erase(p.first.end()-1);
		}
		if (it.front().first[0] == '/'&&it.front().first[1] == '*')  //It is annotation.
			it.front().second = "annotation";
		else {
			for (auto &p : it)
				if (p.first == ")" || p.first == "(" || p.first == "," || p.first == ":-" || p.first == ".")
					p.second = "symbol";
				else if (isupper(p.first[0]))
					p.second = "variable";
				else if (islower(p.first[0]))
					p.second = "atom";
		}
	}
}

void Grammar::handle()
{

}