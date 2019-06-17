#include "Player.h"


Player::Player(int objectCount, Communication* com)
	:GameObject(objectCount), hp(4), score(0), com(com)
{
}


Player::~Player()
{
}

void Player::attack(int id, int objectCount, GameObject* object[])
{
	int probability;
	if (id < ENEMY) {
		probability = rand() % 10;
		Enemy* enemy = dynamic_cast<Enemy*> (object[id]);
		if (probability >= 3) {
			gotoxy(0, HEIGHT + 1);
			printf("공격을 맞췄습니다.");
			addScore(10);
			gotoxy(enemy->getPosition().x, enemy->getPosition().y);
			printf("  ");
			Sleep(2000);
			enemy->dead(object, objectCount);
			update();
			com->gameSendE(id, getPosition().x, getPosition().y,
				enemy->getPosition().x, enemy->getPosition().y);
		}
		else {
			gotoxy(0, HEIGHT + 1);
			printf("공격이 막혔습니다.");
			Sleep(2000);
			update();
			com->gameSend(getPosition().x, getPosition().y);
		}
	}
	else {
		probability = rand() % 10;
		Player* player = dynamic_cast<Player*> (object[id]);
		if (!player) return;

		if (probability >= 5) {
			gotoxy(0, HEIGHT + 1);
			printf("공격을 맞췄습니다.");
			addScore(20);
			player->damage();
			Sleep(2000);
			player->update();
			update();
			com->gameSendP(id, getPosition().x, getPosition().y);
		}
		else {
			gotoxy(0, HEIGHT + 1);
			printf("공격이 막혔습니다.");
			Sleep(2000);
			update();
			com->gameSend(getPosition().x, getPosition().y);
		}
	}
}

bool Player::dead()
{
	if (hp <= 0) {
		return true;
	}
	return false;
}

void Player::addScore(int score)
{
	this->score += score;
}

void Player::damage()
{
	hp -= 1;
}

int Player::getScore()
{
	return score;
}

int Player::getHp()
{
	return hp;
}

void Player::processInput(GameObject* object[], int objectCount)
{
	if (dead()) {
		return;
	}
	int count = 3;
	char c;
	int temp = 0;
	Position myPos = getPosition();

	while (true) {
		c = _getch();
		switch (c)
		{
		case 'w':
			if (count <= 0) {
				gotoxy(0, HEIGHT + 1);
				printf("더 이상 움직일 수 없습니다.");
				Sleep(2000);
				break;
			}
			if (getPosition().y <= 1) {
				gotoxy(0, HEIGHT + 1);
				printf("그 쪽으로 움직일 수 없습니다.");
				Sleep(2000);
				break;
			}
			else if (overlapCheck(0, -1, object, objectCount)) {
				break;
			}
			gotoxy(getPosition().x, getPosition().y);
			printf("  ");
			movePosition(0, -1);
			count -= 1;
			break;
			
		case 'a':
			if (count <= 0) {
				gotoxy(0, HEIGHT + 1);
				printf("더 이상 움직일 수 없습니다.");
				Sleep(2000);
				break;
			}
			if (getPosition().x <= 1) {
				gotoxy(0, HEIGHT + 1);
				printf("그 쪽으로 움직일 수 없습니다.");
				Sleep(2000);
				break;
			}
			else if (overlapCheck(-1, 0, object, objectCount)) {
				break;
			}
			gotoxy(getPosition().x, getPosition().y);
			printf("  ");
			movePosition(-1, 0);
			count -= 1;
			break;

		case 's':
			if (count <= 0) {
				gotoxy(0, HEIGHT + 1);
				printf("더 이상 움직일 수 없습니다.");
				Sleep(2000);
				break;
			}
			if (getPosition().y >= HEIGHT - 1) {
				gotoxy(0, HEIGHT + 1);
				printf("그 쪽으로 움직일 수 없습니다.");
				Sleep(2000);
				break;
			}
			else if (overlapCheck(0, 1, object, objectCount)) {
				break;
			}
			gotoxy(getPosition().x, getPosition().y);
			printf("  ");
			movePosition(0, 1);
			count -= 1;
			break;

		case 'd':
			if (count <= 0) {
				gotoxy(0, HEIGHT + 1);
				printf("더 이상 움직일 수 없습니다.");
				Sleep(2000);
				break;
			}
			if (getPosition().x >= WIDTH - 1) {
				gotoxy(0, HEIGHT + 1);
				printf("그 쪽으로 움직일 수 없습니다.");
				Sleep(2000);
				break;
			}
			else if (overlapCheck(1, 0, object, objectCount)) {
				break;
			}
			gotoxy(getPosition().x, getPosition().y);
			printf("  ");
			movePosition(1, 0);
			count -= 1;
			break;
			
		case 'r':
			gotoxy(getPosition().x, getPosition().y);
			printf("  ");
			setPosition(myPos.x, myPos.y);
			count = 3;
			break;

		case ' ':
			while (true) {
				int order = rand() % objectCount;
				if (order == getId()) {
					continue;
				}
				gotoxy(0, HEIGHT + 1);
				if (order < ENEMY) {
					printf("E%d를 공격하였습니다.", order);
				}
				else {
					printf("P%d를 공격하였습니다.", order - ENEMY + 1);
				}
				Sleep(2000);
				attack(order, objectCount, object);
				return;
			}
			break;
		}
		for (int i = 0; i < objectCount; i++) {
			object[i]->update();
		}
	}
}

void Player::update()
{
	if (dead()) {
		gotoxy(getPosition().x, getPosition().y);
		printf("X");
		return;
	}
	gotoxy(getPosition().x, getPosition().y);
	printf("P%d", getId() - 4);
	gotoxy(0, HEIGHT + 1);
	printf("                                                           ");
	gotoxy(0, HEIGHT + (getId() - ENEMY + 1) * 3);
	printf("플레이어 %d 점수 : %d\n", getId() - ENEMY + 1, getScore());
	printf("          체력 : %d", getHp());
}

bool Player::overlapCheck(int delta_x, int delta_y, GameObject* object[], int objectCount)
{
	GameObject* obj;
	Position pos;
	int temp = 0;
	bool check = false;
	for (int i = 0; i < objectCount; i++) {
		if (i < ENEMY) {
			pos = object[i]->getPosition();
			if (pos.x == getPosition().x + delta_x && pos.y == getPosition().y + delta_y) {
				gotoxy(0, HEIGHT + 1);
				printf("그 쪽으로 움직일 수 없습니다.");
				Sleep(2000);
				return true;
			}
		}
		else {
			pos = object[i]->getPosition();
			if (pos.x == getPosition().x + delta_x && pos.y == getPosition().y + delta_y && check) {
				gotoxy(0, HEIGHT + 1);
				printf("그 쪽으로 움직일 수 없습니다.");
				Sleep(2000);
				return true;
			}
			else if (pos.x == getPosition().x && pos.y == getPosition().y) {
				check = true;
			}
		}
	}
	return false;
}
