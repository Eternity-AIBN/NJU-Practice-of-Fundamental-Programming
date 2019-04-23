#include"User.h"
#include<conio.h>

int User::login()
{
	string name, password;
	cout << "(mysql)==>login:";
	cin >> name;
	cout << "(mysql)==>password:";
	char ch;
	while ((ch = _getch()) != '\r')
	{
		password += ch;
		cout << '*';
	}
	cin.get();
	cout << endl;
	if (name == "user1"&&password == user[0].getInfo().password)
		return 0;
	if (name == "user2"&&password == user[1].getInfo().password)
		return 1;
	if (name == "user3"&&password == user[2].getInfo().password)
		return 2;
	if (name == "user4"&&password == user[3].getInfo().password)
		return 3;
	if (name == "user5"&&password == user[4].getInfo().password)
		return 4;
	if (name == "user6"&&password == user[5].getInfo().password)
		return 5;
	if (name == "user7"&&password == user[6].getInfo().password)
		return 6;
	if (name == "user8"&&password == user[7].getInfo().password)
		return 7;
	return -1;
}