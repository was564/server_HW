#pragma once
#include "Init.h"

class GameObject
{
	Position pos;
	const int id;

public:
	GameObject(int objectCount);
	~GameObject();

	virtual void addscore(int score);
	virtual void damage();
	virtual int getScore();
	virtual bool dead();
	virtual void processInput(GameObject* object[], int objectCount);
	virtual void update();
	void setPosition(int x, int y);
	void movePosition(int x, int y);
	int getId();
	Position getPosition();
};

