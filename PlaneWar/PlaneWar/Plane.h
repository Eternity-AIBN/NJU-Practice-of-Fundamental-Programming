#pragma once
#include"Bullet.h"
#include<atlimage.h>
#include<vector>
using namespace std;

class Plane
{
protected:
	int positionX, positionY;  //飞机(机头)的位置
	int height, width;  //飞机（图片）的高度和宽度
public:
	int getX() const { return positionX; }
	int getY() const { return positionY; }
	int getHeight() const { return height; }
	int getWidth() const { return width; }
};