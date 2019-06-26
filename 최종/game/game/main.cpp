#include "main.h"

void gameOver(GameObject* object[], int objectcount);
void init();

int main() {
	bool power = true;
	int pass, n = 0;
	Communication com;
	while (n > 3 || n < 1) {
		printf("원하시는 항목을 선택해주세요.\n");
		printf("1 : 회원가입, 2 : 로그인, 3 : 종료\n");
		scanf("%d", &n);
		system("cls");
	}
	if (n == 3) {
		return 0;
	}
	com.loginInput(n);
	com.loginSend(n);
	if (!com.loginRecv(&pass)) {
		Sleep(3000);
		return 0;
	}
	srand(com.gameStart());
	while (power) {
		system("cls");
		init();
		int playerCount = 2;
		int objectCount = 0;
		int survive;
		bool gameend = false;
		GameObject* object[MAX];
		for (int i = 0; i < ENEMY; i++) {
			object[i] = new Enemy(objectCount++);
		}
		for (int i = ENEMY; i < ENEMY + playerCount; i++) {
			object[i] = new Player(objectCount++, &com);
		}
		objectCount = ENEMY + playerCount;
		while (true) {
			for (int i = 0; i < objectCount; i++) {
				object[i]->update();
			}
			for (int i = ENEMY; i < ENEMY + playerCount; i++) {
				if (i == pass + ENEMY) {
					object[i]->processInput(object, objectCount);
					gotoxy(WIDTH + 2, 0);
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
				}
				else {
					com.gameRecv(i, object);
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
