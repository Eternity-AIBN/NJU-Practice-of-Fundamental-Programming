#include "stdafx.h"
#include"MyPlane.h"
#include"Enemy.h"
#include"Bullet.h"

bool MyPlane::isDead()
{
	if (lifeValue <= 0)
		return true;
	return false;
}

bool Enemy::isDead(int(*flag)[680])
{
	/*if (flag[positionX - 17][positionY - 4] == 1|| flag[positionX - 17][positionY - 4] == 2)
		return true;

	for (int i = 0; i < 5; ++i)
		if (flag[positionX - 19 + i][positionY - 5] == 1|| flag[positionX - 19 + i][positionY - 5] == 2)
			return true;*/
	return false;
}