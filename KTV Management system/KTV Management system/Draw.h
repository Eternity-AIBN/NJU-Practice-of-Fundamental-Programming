#pragma once
#include<math.h>
#include<windows.h>

class Draw
{
public:
	static void gotoxy(int x, int y);  //����ƶ�
	static void drawVertical(int x, int y, int length, char c = '|');  //����'|'
	static void drawHorizontal(int x, int y, int height, char c = '=');  //���ơ�����
	static void drawRect(int x, int y, int length, int width); //���ƾ���
	static void drawLace(int x, int y, int length, int width); //���ƻ���
	static void drawFrame(int width);  //���Ʊ߿�

};

