#pragma once
#include"Bullet.h"
#include<atlimage.h>
#include<vector>
using namespace std;

class Plane
{
protected:
	int positionX, positionY;  //�ɻ�(��ͷ)��λ��
	int height, width;  //�ɻ���ͼƬ���ĸ߶ȺͿ��
public:
	int getX() const { return positionX; }
	int getY() const { return positionY; }
	int getHeight() const { return height; }
	int getWidth() const { return width; }
};