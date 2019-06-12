#include "stdafx.h"
#include"GameRun.h"
#include <ctime>

GameRun::GameRun():player()
{
	height = GAME_HEIGHT;
	width = GAME_WIDTH;
	player.initImage();
	//载入图片
	Enemy::image.Load(_T("..\\Image\\Enemy.png"));
	transparent(Enemy::image);
	Bullet::image.Load(_T("..\\Image\\Bullet.png"));
	transparent(Bullet::image);
	Enemy e[4];
	for (int i = 0; i < 4; ++i)
	{
		e[i].randProduce(flag);
		enemies.push_back(e[i]);
	}
	score = 0;
}

void GameRun::init()
{
	for (int i = 0; i < 800; ++i)
		for (int j = 0; j < 680; ++j)
			flag[i][j] = 0;
	bullets.clear();
	enemies.clear();
	score = 0;
	srand((unsigned)time(NULL));
}

void GameRun::playerMove(int act)
{
	player.planeMove(act, flag);
}

void GameRun::emenyMove()
{
	for (auto it = enemies.begin(); it != enemies.end(); ++it)
		it->planeMove(flag);
}

void GameRun::randLaunch(Enemy e) //敌机随机发射子弹
{
	Bullet bullet(e.getX()+58, e.getY() + 30, 0, true, flag);
	bullets.push_back(bullet);
}

void GameRun::launchBullet()  //我方发射子弹
{
	Bullet bullet(player.getX()+60, player.getY() - 2, 1, false, flag);
	bullets.push_back(bullet);
}

void GameRun::updateBullets()
{
	for (auto it = bullets.begin(); it != bullets.end();)
		if (it->hit() != 0)
		{
			it->reset(flag);
			it = bullets.erase(it);
		}
		else {
			it->bulletMove(flag);
			++it;
		}
}

void GameRun::updateEnemies()
{
	for (auto it = enemies.begin(); it != enemies.end();)
	{
		if (it->isDead(flag))
		{
			score++;
			it->reset(flag);
			it = enemies.erase(it);
			//还要把飞机的图片清掉
		}
		else { 
			it->planeMove(flag);
			int j = rand() % 10;
			if (j == 3)
				randLaunch(*it);
			++it; 
		}
	}
	if (enemies.size() < 4)
	{
		Enemy enemy;
		enemy.randProduce(flag);
		enemies.push_back(enemy);
	}
}

bool GameRun::gameOver()
{
	return player.isDead();
}