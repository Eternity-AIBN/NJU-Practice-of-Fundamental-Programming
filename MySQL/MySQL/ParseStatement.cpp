#include"ParseStatement.h"

vector<string> ParseStatement::result;
vector<string> ParseStatement::attribute;

void ParseStatement::preProcess(string str)
{
	result.clear();
	attribute.clear();
	for (unsigned int i = 0; i < str.size(); ++i)
	{
		string tmp;
		while (i<str.size() && str[i] != ' '&&str[i] != '('&&str[i] != ')'&&str[i] != ',')
		{
			tmp += str[i];
			++i;
		}
		if (!tmp.empty())
			result.push_back(tmp);
	}
}

int ParseStatement::parse(string str)
{
	preProcess(str);
	if (result.size() < 2)
		return -1;
	if (result[0] == "CREATE"&&result[1] == "TABLE")
		return CREATE;
	if (result[0] == "DROP"&&result[1] == "TABLE")
		return DROP;
	if (result[0] == "TABLE"&&result[1] == "LIST")
		return TABLELIST;
	if (result[0] == "INSERT"&&result[1] == "INTO")
		return INSERT;
	if (result[0] == "DELETE")
		return DELETE;
	if (result[0] == "SELECT")
		return SELECT;
	if (result[0] == "GRANT")
		return GRANT;
	if (result[0] == "REVOKE")
		return REVOKE;
	cout << "Invalid instruction!" << endl;
	return -1;
}