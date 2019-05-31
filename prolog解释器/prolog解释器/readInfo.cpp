#include"lexical.h"
#include<fstream>

bool Lexical::readInfo(string fname)
{
	fname += ".pl";
	ifstream fin(fname);
	if (!fin)
	{
		cout << "The file doesn't exist." << endl;
		return false;
	}
	string lineOfinfo;
	while (fin.peek() != EOF)
	{
		Token tmpToken;
		tokenLine tmpLine;
		getline(fin, lineOfinfo);
		if (lineOfinfo[0] == '/'&&lineOfinfo[1] == '*')  //This line is annotation.
		{
			if (lineOfinfo.size() == 3)  //like "/*/"
				tmpToken.first = lineOfinfo;
			else {
				tmpToken.first = lineOfinfo;
				while (fin.peek() != EOF&&lineOfinfo[lineOfinfo.size() - 2] != '*'&&lineOfinfo[lineOfinfo.size() - 1] != '/')
				{
					getline(fin, lineOfinfo);
					tmpToken.first += lineOfinfo;
				}
			}
			tmpLine.push_back(tmpToken);
		}
		else {
			for (auto it = lineOfinfo.begin(); it != lineOfinfo.end();++it)
			{
				if (*it != '('&&*it != ')'&&*it != ','&&*it != ':'&&*it != '.')
					tmpToken.first += *it;
				else {
					if(*it==':')
						if (it == lineOfinfo.end() - 1 || *(it + 1) != '-') //It's not ":-"
							tmpToken.first += *it;
						else {
							if (!tmpToken.first.empty())
							{
								tmpLine.push_back(tmpToken);  //save the last token
								tmpToken.first.clear();
							}
							tmpToken.first = *it;
							++it;
							tmpToken.first += *it;
							tmpLine.push_back(tmpToken);  //save the new token ":-"
							tmpToken.first.clear();
						}
					else {
						if (!tmpToken.first.empty())
						{
							tmpLine.push_back(tmpToken);  //save the last token
							tmpToken.first.clear();
						}
						tmpToken.first = *it;
						tmpLine.push_back(tmpToken);  //save the new token
						tmpToken.first.clear();
					}
				}
			}
		}
		tokenTable.push_back(tmpLine);
	}
	fin.close();
	return true;
}