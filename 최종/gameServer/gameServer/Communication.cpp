#include "Communication.h"

Communication::Communication()
	:login(false)
{
	memset(buf, '\0', sizeof(buf));
	memset(data, '\0', sizeof(data));
	memset(temp, '\0', sizeof(temp));
}


Communication::~Communication()
{
	closesocket(client_sock);
	printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
}

void Communication::init(LPVOID arg)
{
	client_sock = (SOCKET)arg;
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (SOCKADDR*)& clientaddr, &addrlen);
}

void Communication::loginRecv()
{
	memset(buf, 0, sizeof(buf));
	retval = recv(client_sock, buf, BUFSIZE, 0);
	if (retval == SOCKET_ERROR) {
		err_display("recv()");
		exit(1);
	}
	if (buf[0] == 1) {
		strncpy(id, &buf[2], (int)buf[1]);
		strncpy(pw, &buf[3 + strlen(id)], (int)buf[2 + strlen(id)]);
	}
	else if (buf[0] == 7) {
		strncpy(id, &buf[2], (int)buf[1]);
		strncpy(pw, &buf[3 + strlen(id)], (int)buf[2 + strlen(id)]);
		getRegist(id, pw);
	}
}

bool Communication::loginSend(int index)
{
	char id[20];
	char pw[20];
	memset(buf, 0, sizeof(buf));
	ifstream file("login.txt");
	bool check = false;
	while (!file.eof()) {
		check = false;
		file.getline(id, 20);
		file.getline(pw, 20);
		if (!strcmp(id, this->id)) {
			if (!strcmp(pw, this->pw)) {
				check = true;
				break;
			}
		}
	}
	socket2(buf, index, check);

	retval = send(client_sock, buf, retval, 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
		exit(1);
	}
	if (check) {
		pass = index;
		play[pass] = client_sock;
		return true;
	}
	else {
		return false;
	}
}

void Communication::getRegist(char* id, char* pw)
{
	ofstream outFile("login.txt", ios::app);
	outFile << id << endl;
	outFile << pw << endl;
	outFile.close();
}

void Communication::gameStart()
{
	memset(buf, 0, sizeof(buf));
	socket3(buf);
	retval = send(client_sock, buf, retval, 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
		exit(1);
	}
}

void Communication::gameRecvNSend()
{
	memset(buf, 0, sizeof(buf));
	retval = recv(client_sock, buf, BUFSIZE, 0);
	if (retval == SOCKET_ERROR) {
		err_display("recv()");
		exit(1);
	}
	if (buf[0] >= 4 && buf[0] <= 6) {
		for (int i = 0; i < PLAYER; i++) {
			if (i == pass) {
				continue;
			}
			retval = send(play[i], buf, retval, 0);
			if (retval == SOCKET_ERROR) {
				err_display("send()");
				exit(1);
			}
		}
	}
}

void Communication::file_init()
{
	ofstream outFile("login.txt");
	outFile << "1" << endl;
	outFile << "1" << endl;
	outFile << "2" << endl;
	outFile << "2" << endl;
	outFile.close();
}

int Communication::getPass()
{
	return pass;
}
