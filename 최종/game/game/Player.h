#pragma once
#include "Init.h"
#include "Communication.h"
#include "GameObject.h"
#include "Enemy.h"
#include <cmath>

class Player : public GameObject
{
	int hp;
	int score;
	Communication* com;
public:
	Player(int objectCount, Communication* com);
	~Player();

	void attack(int id, int objectCount, GameObject* object[]);
	bool dead();
	void addScore(int score);
	void damage();
	int getScore();
	int getHp();
	void processInput(GameObject* object[], int objectCount);
	void update();
	bool overlapCheck(int delta_x, int delta_y, GameObject* object[], int objectCount);
};