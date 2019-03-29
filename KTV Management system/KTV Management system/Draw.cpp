#include"Draw.h"
#include<iostream>
using namespace std;
void Draw::gotoxy(int x, int y)
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}
void Draw::drawHorizontal(int x, int y, int length, char c)
{
	gotoxy(x, y);
	for (int i = 0; i < length; ++i)
		cout << c;
}
void Draw::drawVertical(int x, int y, int height, char c)
{
	for (int i = 0; i < height; ++i)
	{
		gotoxy(x , y + i);
		cout << c;
	}
}
void Draw::drawRect(int x, int y, int length, int width)
{
	drawHorizontal(x + 1, y - 1, length - 1);
	drawVertical(x, y, width);
	drawHorizontal(x + 1, y + width, length - 1);
	drawVertical(x + length, y, width);
}
void Draw::drawLace(int x, int y, int length, int width)
{
	drawHorizontal(x, y - 1, length + 1, '*');
	drawVertical(x, y, width, '*');
	drawHorizontal(x, y + width, length + 1, '*');
	drawVertical(x + length, y, width, '*');
}
void Draw::drawFrame(int width)
{
	gotoxy(40, 5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << "KTVµã¸èÏµÍ³";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	drawLace(25, 7, 40, width);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	drawRect(26, 8, 38, width - 2);
}
