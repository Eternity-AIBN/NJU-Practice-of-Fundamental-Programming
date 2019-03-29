#pragma once
#include<math.h>
#include<windows.h>

class Draw
{
public:
	static void gotoxy(int x, int y);  //光标移动
	static void drawVertical(int x, int y, int length, char c = '|');  //绘制'|'
	static void drawHorizontal(int x, int y, int height, char c = '=');  //绘制‘—’
	static void drawRect(int x, int y, int length, int width); //绘制矩形
	static void drawLace(int x, int y, int length, int width); //绘制花边
	static void drawFrame(int width);  //绘制边框

};

