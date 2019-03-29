#include<iostream>
using namespace std;
#include"Draw.h"
#include"MainInterface.h"
#include"AdminInterface.h"
#include"UserInterface.h"
#include"IdAndPassword.h"

int main()
{
	ios::sync_with_stdio(false);

	IdAndPassword idAndPassword;
	system("mode 100,30");

	idAndPassword.printChange();
	idAndPassword.changePassword();
	while (1)
	{
		MainInterface::printMain();
		int choice = MainInterface::mainChoice();
		if (choice == 0)
		{
			MainInterface::printLogin();
			if (idAndPassword.judge())
				AdminInterface::printAdmin();
			else break;
		}
		if (choice == 1)
			UserInterface::printUser();
	}
	return 0;
}