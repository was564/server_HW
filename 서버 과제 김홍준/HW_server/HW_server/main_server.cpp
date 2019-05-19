#include "main_server.h"

// 클라이언트와 데이터 통신
DWORD WINAPI ProcessClient(LPVOID arg);

int main(int argc, char* argv[])
{
	initialization init;
	init.Bind();
	init.Listen();
	while (1) {
		init.Accept();
	}

	return 0;
}

DWORD WINAPI ProcessClient(LPVOID arg)
{
	Comunication com;
	com.Init(arg);
	if (!com.FirstRecv()) {
		return 0;
	}
	if (!com.FirstSend()) {
		return 0;
	}
	if (!com.SecondRecv()) {
		return 0;
	}
	com.ChangeShare();
	while (1) {
		if (!com.Recv()) {
			return 0;
		}
		if (!com.Send()) {
			return 0;
		}
	}
	return 0;
}