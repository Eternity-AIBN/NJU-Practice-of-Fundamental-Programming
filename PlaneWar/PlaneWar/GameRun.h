#pragma once
#include"Bullet.h"
#include"Enemy.h"
#include"MyPlane.h"
#include<vector>
using namespace std;

class GameRun
{
private:
	MyPlane player;
	int score;
	int height, width; //��Ϸ����߶ȺͿ��
	static const int GAME_HEIGHT = 800;
	static const int GAME_WIDTH = 680;

	int flag[800][680];

public:
	vector<Bullet> bullets;
	vector<Enemy> enemies;

	GameRun();
	int getHeight() { return height; }
	int getWidth() { return width; }
	int getScore() const { return score; }
	void init();
	void playerMove(int act);
	void emenyMove();
	void updateBullets();
	void updateEnemies();
	void launchBullet();  //�ҷ������ӵ�
	void randLaunch(Enemy e);  //�л���������ӵ� 
	bool gameOver();
	const MyPlane &getPlanePlayer() const { return player; }
	const vector<Enemy> &getEnemy() const { return enemies; }
	const vector<Bullet> &getBullet() const { return bullets; }

};