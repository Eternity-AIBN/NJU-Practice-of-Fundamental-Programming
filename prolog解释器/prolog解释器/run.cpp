#include"lexical.h"
#include"grammar.h"
#include<fstream>

bool Lexical::run(string fname)
{
	if (!readInfo(fname))
		return false;
	handle();
	checkError();
	if (allErrors.size() != 0)
		return false;
	return true;
}

bool Grammar::run()
{
	checkError();
	if (allErrors.size() != 0)
		return false;
	/*while (1) //Todo���޸��˳�ѭ��������
	{
		consultFact();
	}*/
	return true;
}