#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS // 최신 VC++ 컴파일 시 경고 방지
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <conio.h>

using namespace std;

#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE    512
#define WIDTH 40
#define HEIGHT 20
#define ENEMY 5
#define MAX 20

using namespace std;

struct Position {
	int x;
	int y;
	Position() {
		x = (rand() % (WIDTH - 2)) + 1, y = (rand() % (HEIGHT - 2)) + 1;
	}
};

extern void gotoxy(short int x, short int y);