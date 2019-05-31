#include"lexical.h"
#include"grammar.h"
#include<fstream>

void Lexical::saveIn()
{
	ofstream fout("token.txt");
	if (!fout)
	{
		cout << "Save table error." << endl;
		return;
	}
	for (auto it : tokenTable)
	{
		for (auto p : it)
			fout << p.first << '\t' << p.second << endl;
		fout << endl;
	}
	fout.close();
}

bool Lexical::run(string fname)
{
	if (!readInfo(fname))
		return false;
	handle();
	checkError();
	//if (allErrors.size() != 0)
		//return false;
	saveIn();
	return true;
}

void Grammar::run()
{

}