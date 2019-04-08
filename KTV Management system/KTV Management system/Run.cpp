#include"AdminInterface.h"
#include"UserInterface.h"
#include"MainInterface.h"
#include"InfoHandle.h"
#include"IdAndPassword.h"

extern IdAndPassword idAndPassword;

void AdminInterface::run()
{
	MainInterface::printLogin();
	if (idAndPassword.judge())
		while (1)
		{
			AdminInterface::printAdmin();
			int choice = AdminInterface::adminChoice();
			switch (choice)
			{
			case 0:InfoHandle::songInquire(); break;
			case 1:InfoHandle::addSong(); break;
			case 2:InfoHandle::bulkImport(); break;
			case 3:InfoHandle::deleteSong(); break;
			case 4:InfoHandle::modifyInfo(); break;
			case 5:InfoHandle::songRanking(); break;
			case 6: {
				idAndPassword.printChange();
				idAndPassword.changePassword();
				break;
			}
			case 7:return;
			}
		}
	else return;
}

void UserInterface::run()
{
	InfoHandle info;
	UserInterface::printUser();
	while (1)
	{
		UserInterface::printUser();
		if (backToUser)
		{
			PlayMusic play;
			PlayMusic *const this1 = &play;
			play.th1 = thread(&PlayMusic::playMusic, this1);
			play.th2 = thread(&PlayMusic::printLyrics, this1);
			play.th1.detach();
			play.th2.detach();
		}
		int choice = UserInterface::userChoice();
		switch (choice)
		{
		case 0:info.chooseSinger(); break;
		case 1:info.chooseSongName(); break;
		case 2:info.choosePhoneticize(); break;
		case 3:info.haveSelected(); break;
		case 4:backToMain = true; backToUser = true; return;
		}
	}
}