#include"lexical.h"
#include"grammar.h"
#include<iostream>
#include<fstream>
using namespace std;
Lexical lex;

void saveIn(Lexical &lex, string fname)  //To save the token table into the file token.txt
{
	ofstream fout("token.txt", ios::app);
	if (!fout)
	{
		cout << "Save table error." << endl;
		return;
	}
	fname += ".pl";
	fout << fname << "：" << endl;
	for (auto it : lex.tokenTable)
	{
		for (auto p : it.first)
			fout << p.first << '\t' << p.second << endl;
		fout << endl;
	}
	fout.close();
}

void run()
{
	string fname, tmp;
	while (1)
	{
		Grammar gra;

		cout << "?- ";
		cin >> fname;
		if (fname == "halt.")  //Exit the prolog
			return;
		if(fname.size()<10)
			cout << "Invalid command." << endl;
		else {
			tmp.assign(fname, 0, 8);
			if (tmp == "consult("&&*(fname.end()-2)==')'&&fname.back() == '.')  //The command is valid.
			{
				fname.assign(fname, 8, fname.size() - 10);
				if (lex.run(fname)&&gra.run())  //Open file successfully and the file is correct.
				{
					saveIn(lex, fname);
					return;
					
					//gra.consultFact();
					//Todo:改为循环，输入halt退出整个run
				}
				lex.tokenTable.clear(); 
				lex.allErrors.clear();
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