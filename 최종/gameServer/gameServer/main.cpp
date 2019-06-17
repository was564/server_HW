#include "main.h"

static int players = 0;
CRITICAL_SECTION   hCriticalSection;
void IncreaseCount();
DWORD WINAPI ProcessClient(LPVOID arg);

int main()
{
	InitializeCriticalSection(&hCriticalSection);
	srand((unsigned int)time(NULL));
	Initialization init;
	init.Bind();
	init.Listen();
	while (1) {
		init.Accept();
	}

	DeleteCriticalSection(&hCriticalSection);
	return 0;
}

DWORD WINAPI ProcessClient(LPVOID arg)
{
	Communication com;
	com.init(arg);
	com.file_init();
	com.loginRecv();
	if (com.loginSend(players)) {
		IncreaseCount();
	}
	while (true) {
		if (players >= PLAYER) {
			com.gameStart();
			break;
		}
	}
	while (true) {
		com.gameRecvNSend();
	}
	return 0;
}

void IncreaseCount() {
	EnterCriticalSection(&hCriticalSection);
	players++;
	LeaveCriticalSection(&hCriticalSection);
}