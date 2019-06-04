#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <conio.h>

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