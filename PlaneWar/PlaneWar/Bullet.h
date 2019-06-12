#pragma once
#include<atlimage.h>
#include<vector>
using namespace std;

extern void transparent(CImage &img);

class Bullet
{
	int positionX, positionY;   //�ӵ�������
	int height, width;
	bool direction;              //�ӵ��ķ���,1����,0����
	
public:
	static CImage image;         //�ӵ���ͼƬ
	bool whoShoot;               //˭������ӵ���0�һ���1�л�

	int getX() const { return positionX; }
	int getY() const { return positionY; }
	int getHeight() const { return height; }
	int getWidth() const { return width; }

	Bullet() { height = 20; width = 10; }
	Bullet(int x, int y, bool dir, bool who, int(*flag)[680]);
	void reset(int(*flag)[680]){ flag[positionX - 17][positionY - 5] = 0; }
	void bulletMove(int(*flag)[680]);          //�ӵ��ƶ�
	bool hit();               //�ж��Ƿ���б߽�

	const CImage &getImage() const { return image; }
	void initImage(); 
};
