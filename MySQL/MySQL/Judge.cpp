#include"User.h"

bool User::judge(string tName, string per)
{
	if (user[n].pofUser.size() == 0)
		return false;
	unsigned int i = 0;
	for (; i < user[n].pofUser.size(); ++i)
		if (user[n].pofUser[i].tableName == tName)
			break;
	if (user[n].pofUser[i].isOwner == true)
		return true;
	for (unsigned int j = 0; j < user[n].pofUser[i].perm.size(); ++j)
		if (user[n].pofUser[i].perm[j] == per)
			return true;
	return false;
}