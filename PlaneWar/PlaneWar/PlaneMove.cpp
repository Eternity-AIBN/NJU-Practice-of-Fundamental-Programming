#include "stdafx.h"
#include"Enemy.h"
#include"MyPlane.h"
#include<conio.h>

void Enemy::planeMove(int(*flag)[680])
{
	/*flag[positionX - 17][positionY - 5] = 0;
	for (int i = 0; i < 5; ++i)
		flag[positionX - 19 + i][positionY - 6] = 0;*/
	positionY += 5;
	/*int i = rand() % 4;

	switch (i)
	{
	case 0: {
		if (positionX > 0)
			positionX -= 20;
		break;
	}
	case 1: {
		if (positionX < 609)
			positionX += 20;
		break;
	}
	case 2: {
		if (positionY > 19)
			positionY -= 15;
		break;
	}
	case 3: {
		if (positionY < 599)
			positionY += 15;
		break;
	}
	}*/
}

void MyPlane::planeMove(int act, int(*flag)[680])
{

	/*flag[positionX - 17][positionY - 5] = 0;
	flag[positionX - 16][positionY - 5] = 0;
	for (int i = 0; i < 4; ++i)
		flag[positionX - 18 + i][positionY - 4] = 0;*/

	switch (act)
	{
	case moveUp: {
		if (positionY > 19)
			positionY -= 20;
		break;
	}
	case moveDown: {
		if (positionY < 779)
			positionY += 20;
		break;
	}
	case moveLeft: {
		if (positionX > 0)
			positionX -= 30;
		break;
	}
	case moveRight: {
		if (positionX < 609)
			positionX += 30;
		break;
	}
	default:
		break;
	}

}