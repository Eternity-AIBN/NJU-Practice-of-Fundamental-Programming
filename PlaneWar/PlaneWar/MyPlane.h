#pragma once
#include"Plane.h"

#define moveUp 1
#define moveDown 2
#define moveLeft 3
#define moveRight 4

class MyPlane :public Plane
{
	int lifeValue;   //我方战机生命值
	CImage image;
public:
	MyPlane() { positionX = 280; positionY = 600; height = 100; width = 140; lifeValue = 20; }     //初始化
	void planeMove(int act, int(*flag)[680]);  //玩家控制飞机移动
	bool isDead();     //判断是否死亡
	void healthReduction(int(*flag)[680]);  //生命值减少

	const CImage &getImage() const { return image; }
	void initImage(); 
};
