#pragma once
#include "Init.h"
#include "GameObject.h"

class Enemy : public GameObject
{

public:
	Enemy(int objectCount);
	~Enemy();

	bool dead(GameObject* object[], int objectCount);
	void update();
};

