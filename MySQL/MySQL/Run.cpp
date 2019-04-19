#include"User.h"

extern User user[8];
extern vector<Table> tables;

void User::run(int n)
{
	string s;
	getline(cin, s);
	int choice = ParseStatement::parse(s);
	switch (choice)
	{
	case CREATE:user[n].createTable(); break;
	case DROP:break;
	case INSERT:break;
	case DELETE:break;
	case TABLELIST:break;
	case GRANT:break;
	case REVOKE:break;
	default:
		break;
	}
}