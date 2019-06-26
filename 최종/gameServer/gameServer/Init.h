#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define SERVERPORT 9000
#define BUFSIZE    512
#define WIDTH 40
#define HEIGHT 20
#define ENEMY 5
#define MAX 20
#define PLAYER 2

static SOCKET play[2];