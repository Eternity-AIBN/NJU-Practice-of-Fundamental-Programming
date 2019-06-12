#pragma once
#include"stdafx.h"
#include"Bullet.h"
#include"Enemy.h"
#include"MyPlane.h"
#include<conio.h>
extern vector<Enemy> enemies;

void Bullet::run()
{
	for (auto it = bullets.begin(); it != bullets.end();)
		if (it->hit() != 0)
			it = bullets.erase(it);
		else {
			it->bulletMove();
			++it;
		}
}

void Enemy::run()
{
	for (auto it = enemies.begin(); it != enemies.end();)
	{
		if (it->isDead())
		{
			score++;
			it = enemies.erase(it);
		}
		else {
			it->renderPlane();
			++it;
		}
	}
	if (enemies.size() < 4)
	{
		Enemy enemy;
		enemy.randProduce();
		enemies.push_back(enemy);
	}
}

void MyPlane::run()
{
	Enemy enemy;
	enemy.randProduce();
	enemies.push_back(enemy);

	while (!isDead())
	{
		renderPlane();
		while (!_kbhit())
		{
			Bullet::run();
			Enemy::run();
			Sleep(100);
			healthReduction();
			for (auto it = bullets.begin(); it != bullets.end(); ++it)
				it->bulletMove();
			for (auto it = enemies.begin(); it != enemies.end(); ++it)
				it->planeMove();
		}
		planeMove();
	}
}