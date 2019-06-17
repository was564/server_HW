#include "GameObject.h"

GameObject::GameObject(int objectCount)
	:pos(), id(objectCount)
{
}

GameObject::~GameObject()
{
}

void GameObject::addscore(int score)
{
}

void GameObject::damage()
{
}

int GameObject::getScore()
{
	return 0;
}

bool GameObject::dead()
{
	return false;
}

void GameObject::processInput(GameObject* object[], int objectCount)
{
}

void GameObject::update()
{
}

void GameObject::setPosition(int x, int y)
{
	pos.x = x, pos.y = y;
}

void GameObject::movePosition(int x, int y)
{
	pos.x += x;
	pos.y += y;
}

int GameObject::getId()
{
	return id;
}

Position GameObject::getPosition()
{
	return pos;
}
