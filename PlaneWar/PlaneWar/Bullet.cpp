#include "stdafx.h"
#include"Bullet.h"
using namespace std;

Bullet::Bullet(int x, int y, bool dir, bool who,int (*flag)[680])
{
	positionX = x;
	positionY = y;
	direction = dir;
	whoShoot = who;
	height = 80;
	width = 50;

	/*if (whoShoot)
		flag[positionX - 17][positionY - 5] = 4;
	else flag[positionX - 17][positionY - 5] = 1;*/
}

void Bullet::bulletMove(int(*flag)[680])
{
	//flag[positionX - 17][positionY - 5] = 0;

	if (direction)
		positionY -= 40;
	else positionY += 40;
	/*if (whoShoot)
		flag[positionX - 17][positionY - 5] = 4;
	else flag[positionX - 17][positionY - 5] = 1;*/
}

bool Bullet::hit()
{
	if (positionY == 1 || positionY == 799)
		return 1;
	return 0;
}

void Bullet::initImage() {
	if (image.Load(_T("..\\Image\\Bullet.png")) != S_OK)
		AfxMessageBox(_T("Error in loading Bullet picture"));
	//image.Load(_T("..\\Image\\Bullet.png"));
	transparent(image);
}

CImage Bullet::image;