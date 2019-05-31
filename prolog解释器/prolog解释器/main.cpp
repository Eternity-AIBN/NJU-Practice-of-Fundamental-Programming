#include"lexical.h"
#include"grammar.h"
#include<iostream>
using namespace std;

void run()
{
	Lexical lex;
	Grammar gra;

	string fname, tmp;
	while (1)
	{
		cout << "?-";
		cin >> fname;
		if(fname.size()<10)
			cout << "Invalid command." << endl;
		else {
			tmp.assign(fname, 0, 8);
			if (tmp == "consult("&&*(fname.end()-2)==')'&&fname.back() == '.')  //The command is valid.
			{
				fname.assign(fname, 8, fname.size() - 10);
				if (lex.run(fname))  //Open file successfully and the file is correct.
				{
					gra.run();
					return;
				}
			}
			else cout << "Invalid command." << endl;
		}
	}
}
int main()
{
	run();
	return 0;
}