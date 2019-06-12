#pragma once
#include"Plane.h"

#define moveUp 1
#define moveDown 2
#define moveLeft 3
#define moveRight 4

class MyPlane :public Plane
{
	int lifeValue;   //�ҷ�ս������ֵ
	CImage image;
public:
	MyPlane() { positionX = 280; positionY = 600; height = 100; width = 140; lifeValue = 20; }     //��ʼ��
	void planeMove(int act, int(*flag)[680]);  //��ҿ��Ʒɻ��ƶ�
	bool isDead();     //�ж��Ƿ�����
	void healthReduction(int(*flag)[680]);  //����ֵ����

	const CImage &getImage() const { return image; }
	void initImage(); 
};
