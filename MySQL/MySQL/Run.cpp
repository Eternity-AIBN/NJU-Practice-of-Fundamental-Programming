#include"User.h"

void User::run()
{
	string s;
	cout << "(mysql)==>";
	getline(cin, s);
	while (s != "quit")
	{
		int choice = ParseStatement::parse(s);
		switch (choice)
		{
		case CREATE:user[n].createTable(); break;
		case DROP:user[n].dropTable(); break;
		case INSERT:user[n].insertInto(); break;
		case DELETE:user[n].deleteFrom(); break;
		case TABLELIST:user[n].tableList(); break;
		case GRANT:break;
		case REVOKE:break;
		default:
			break;
		}
		cout << "(mysql)==>";
		getline(cin, s);
	}
}