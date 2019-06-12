#include "stdafx.h"
#include"Enemy.h"

void Enemy::randProduce(int(*flag)[680])
{
	positionX = rand() % 680;
	positionY = rand() % 400;

	//flag[positionX - 17][positionY - 5] = 3;
}