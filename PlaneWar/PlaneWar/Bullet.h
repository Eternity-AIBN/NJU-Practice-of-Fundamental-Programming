#pragma once
#include<atlimage.h>
#include<vector>
using namespace std;

extern void transparent(CImage &img);

class Bullet
{
	int positionX, positionY;   //子弹的坐标
	int height, width;
	bool direction;              //子弹的方向,1向上,0向下
	
public:
	static CImage image;         //子弹的图片
	bool whoShoot;               //谁发射的子弹，0我机，1敌机

	int getX() const { return positionX; }
	int getY() const { return positionY; }
	int getHeight() const { return height; }
	int getWidth() const { return width; }

	Bullet() { height = 20; width = 10; }
	Bullet(int x, int y, bool dir, bool who, int(*flag)[680]);
	void reset(int(*flag)[680]){ flag[positionX - 17][positionY - 5] = 0; }
	void bulletMove(int(*flag)[680]);          //子弹移动
	bool hit();               //判断是否击中边界

	const CImage &getImage() const { return image; }
	void initImage(); 
};
