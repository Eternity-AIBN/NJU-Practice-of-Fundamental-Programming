#pragma once
#include"Plane.h"
#include<ctime>
#include<cstdlib>

class Enemy :public Plane
{
public:
	static CImage image;
	Enemy() { height = 100; width = 120; }              //初始化
	void reset(int(*flag)[680]) {
		flag[positionX - 17][positionY - 5] = 0;
		for (int i = 0; i < 5; ++i)
			flag[positionX - 19 + i][positionY - 6] = 0;
	}
	void randProduce(int(*flag)[680]);         //随机产生飞机
	void planeMove(int(*flag)[680]);  //飞机随机移动
	bool isDead(int(*flag)[680]);     //判断是否死亡

	const CImage &getImage() const{ return image; }
	void initImage();
};