#include "Enemy.h"

Enemy::Enemy(int objectCount)
	:GameObject(objectCount)
{
}

Enemy::~Enemy()
{
}

bool Enemy::dead(GameObject* object[], int objectCount)
{
	int check;
	while (true) {
		check = 0;
		gotoxy(getPosition().x, getPosition().y);
		printf("  ");
		setPosition((rand() % (WIDTH - 2)) + 1, (rand() % (HEIGHT - 2)) + 1);
		for (int i = 0; i < objectCount; i++) {
			if (getId() == i) {
				continue;
			}
			if (getPosition().x == object[i]->getPosition().x) {
				if (getPosition().y == object[i]->getPosition().y) {
					check = 1;
				}
			}
		}
		if (check == 0) {
			break;
		}
	}
	update();
	return true;
}

void Enemy::update()
{
	gotoxy(getPosition().x, getPosition().y);
	printf("E%d", getId());
}
