#include "main.h"

void gameOver(GameObject* object[], int objectcount);
void init();

int main() {
	bool power = true;
	Communication com;
	com.loginInput();
	com.loginSend();
	com.loginRecv();
	while (power) {
		srand((unsigned int)time(NULL));
		system("cls");
		init();
		int turn = 0;
		int playerCount;
		int objectCount = 0;
		int survive;
		bool gameend = false;
		GameObject* object[MAX];
		for (int i = 0; i < ENEMY; i++) {
			object[i] = new Enemy(objectCount++);
		}
		gotoxy(0, HEIGHT + 1);
		cout << "플레이어 수 : ";
		cin >> playerCount;
		for (int i = ENEMY; i < ENEMY + playerCount; i++) {
			object[i] = new Player(objectCount++);
		}
		objectCount = ENEMY + playerCount;
		while (true) {
			for (int i = 0; i < objectCount; i++) {
				object[i]->update();
			}
			for (int i = ENEMY; i < ENEMY + playerCount; i++) {
				object[i]->processInput(object, objectCount);
				turn++;
				gotoxy(WIDTH + 2, 0);
				printf("턴 : %d", turn);
				survive = 0;
				for (int i = ENEMY; i < ENEMY + playerCount; i++) {
					if (!object[i]->dead()) {
						survive++;
					}
				}
				if (survive <= 1) {
					gameend = true;
					break;
				}
				else if (turn >= 20) {
					gameend = true;
					break;
				}
			}
			if (gameend) {
				break;
			}
			for (int i = 0; i < objectCount; i++) {
				object[i]->update();
			}
		}
		gameOver(object, objectCount);
		gotoxy(0, 4);
		printf("그만하시겠습니까? (y/n) : ");
		while (true) {
			char answer = _getch();
			if (answer == 'n') {
				power = false;
				break;
			}
			else if (answer == 'y') {
				power = true;
				break;
			}
			else {
				continue;
			}
		}
		for (int i = 0; i < objectCount; i++) {
			delete object[i];
		}
	}

	return 0;
}

void gameOver(GameObject* object[], int objectCount)
{
	system("cls");
	gotoxy(0, 0);
	printf("	점수 : ");
	int max = 0;
	for (int i = ENEMY; i < objectCount; i++) {
		if (max < object[i]->getScore()) {
			max = object[i]->getScore();
		}
	}
	printf("%d\n", max);
	printf("Winner : ");
	for (int i = ENEMY; i < objectCount; i++) {
		if (max == object[i]->getScore()) {
			printf("Player %d ", i - ENEMY + 1);
		}
	}
	Sleep(3000);
}

void gotoxy(short int x, short int y)
{
	COORD pos = { x * 2, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void init()
{
	for (short int i = 0; i <= HEIGHT; i++) {
		gotoxy(0, i);
		printf("■");
		gotoxy(WIDTH, i);
		printf("■");
	}
	string s = "";
	for (short int i = 0; i <= WIDTH; i++) {
		s.append("■");
	}
	gotoxy(0, 0);
	printf(s.c_str());
	gotoxy(0, HEIGHT);
	printf(s.c_str());
}
