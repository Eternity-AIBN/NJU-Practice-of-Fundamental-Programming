#include"UserInterface.h"
#include<iostream>
using namespace std;
void UserInterface::printUser()
{
	system("mode 100,30");
	system("cls");
	Draw::drawFrame(15);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
	Draw::gotoxy(36, 10);
	cout << "=>";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
	Draw::gotoxy(39, 10);
	cout << "0.歌手点歌";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
	Draw::gotoxy(39, 12);
	cout << "1.歌名点歌";
	Draw::gotoxy(39, 14);
	cout << "2.拼音点歌";
	Draw::gotoxy(39, 16);
	cout << "3.已点歌曲";
	Draw::gotoxy(39, 18);
	cout << "4.返回主界面";
}
int UserInterface::userChoice()
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
				case 0:Draw::gotoxy(36, 10); cout << "   0.歌手点歌"; break;
				case 1:Draw::gotoxy(36, 12); cout << "   1.歌名点歌"; break;
				case 2:Draw::gotoxy(36, 14); cout << "   2.拼音点歌"; break;
				case 3:Draw::gotoxy(36, 16); cout << "   3.已点歌曲"; break;
				case 4:Draw::gotoxy(36, 18); cout << "   4.返回主界面"; break;
				default:
					break;
				}
				if (str == 80)
					choiceNum++;
				else choiceNum += 4;
				choiceNum %= 5;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
				Draw::gotoxy(36, 10 + choiceNum * 2);
				cout << "=>";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
				switch (choiceNum)
				{
				case 0:Draw::gotoxy(39, 10); cout << "0.歌手点歌"; break;
				case 1:Draw::gotoxy(39, 12); cout << "1.歌名点歌"; break;
				case 2:Draw::gotoxy(39, 14); cout << "2.拼音点歌"; break;
				case 3:Draw::gotoxy(39, 16); cout << "3.已点歌曲"; break;
				case 4:Draw::gotoxy(39, 18); cout << "4.返回主界面"; break;
				default:
					break;
				}
			}
		}
	}
	return choiceNum;
}