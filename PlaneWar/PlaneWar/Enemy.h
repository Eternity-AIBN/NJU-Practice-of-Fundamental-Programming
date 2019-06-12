#pragma once
#include"Plane.h"
#include<ctime>
#include<cstdlib>

class Enemy :public Plane
{
public:
	static CImage image;
	Enemy() { height = 100; width = 120; }              //��ʼ��
	void reset(int(*flag)[680]) {
		flag[positionX - 17][positionY - 5] = 0;
		for (int i = 0; i < 5; ++i)
			flag[positionX - 19 + i][positionY - 6] = 0;
	}
	void randProduce(int(*flag)[680]);         //��������ɻ�
	void planeMove(int(*flag)[680]);  //�ɻ�����ƶ�
	bool isDead(int(*flag)[680]);     //�ж��Ƿ�����

	const CImage &getImage() const{ return image; }
	void initImage();
};