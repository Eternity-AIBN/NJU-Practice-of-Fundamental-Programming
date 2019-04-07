#include"AdminInterface.h"
#include<iostream>
using namespace std;
void AdminInterface::printAdmin()
{
	system("mode 100,33");
	system("cls");
	Draw::drawFrame(21);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
	Draw::gotoxy(36, 10);
	cout << "=>";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
	Draw::gotoxy(39, 10);
	cout << "0.歌曲信息查询";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
	Draw::gotoxy(39, 12);
	cout << "1.增加歌曲";
	Draw::gotoxy(39, 14);
	cout << "2.批量导入";
	Draw::gotoxy(39, 16);
	cout << "3.删除歌曲";
	Draw::gotoxy(39, 18);
	cout << "4.修改歌曲信息";
	Draw::gotoxy(39, 20);
	cout << "5.歌曲排行";
	Draw::gotoxy(39, 22);
	cout << "6.修改密码";
	Draw::gotoxy(39, 24);
	cout << "7.返回主界面";
}
int AdminInterface::adminChoice()
{
	int str;
	int choiceNum = 0;
	while ((str = _getch()) != 13) {
		if (str == 224)
		{
			str = _getch();
			if (str == 80 || str == 72)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
				switch (choiceNum)
				{
				case 0:Draw::gotoxy(36, 10); cout << "   0.歌曲信息查询"; break;
				case 1:Draw::gotoxy(36, 12); cout << "   1.增加歌曲"; break;
				case 2:Draw::gotoxy(36, 14); cout << "   2.批量导入"; break;
				case 3:Draw::gotoxy(36, 16); cout << "   3.删除歌曲"; break;
				case 4:Draw::gotoxy(36, 18); cout << "   4.修改歌曲信息"; break;
				case 5:Draw::gotoxy(36, 20); cout << "   5.歌曲排行"; break;
				case 6:Draw::gotoxy(36, 22); cout << "   6.修改密码"; break;
				case 7:Draw::gotoxy(36, 24); cout << "   7.返回主界面"; break;
				default:
					break;
				}
				if (str == 80)
					choiceNum++;
				else choiceNum += 7;
				choiceNum %= 8;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
				Draw::gotoxy(36, 10 + choiceNum * 2);
				cout << "=>";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
				switch (choiceNum)
				{
				case 0:Draw::gotoxy(39, 10); cout << "0.歌曲信息查询"; break;
				case 1:Draw::gotoxy(39, 12); cout << "1.增加歌曲"; break;
				case 2:Draw::gotoxy(39, 14); cout << "2.批量导入"; break;
				case 3:Draw::gotoxy(39, 16); cout << "3.删除歌曲"; break;
				case 4:Draw::gotoxy(39, 18); cout << "4.修改歌曲信息"; break;
				case 5:Draw::gotoxy(39, 20); cout << "5.歌曲排行"; break;
				case 6:Draw::gotoxy(39, 22); cout << "6.修改密码"; break;
				case 7:Draw::gotoxy(39, 24); cout << "7.返回主界面"; break;
				default:
					break;
				}
			}
		}
	}
	return choiceNum;
}