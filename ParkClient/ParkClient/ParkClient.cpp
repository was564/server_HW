#define _CRT_SECURE_NO_WARNINGS         // 최신 VC++ 컴파일 시 경고 방지
#define _WINSOCK_DEPRECATED_NO_WARNINGS // 최신 VC++ 컴파일 시 경고 방지
#include<WinSock2.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
#pragma comment(lib,"ws2_32.lib")
#define BUFSIZE 1024
class m_Socket {
private:
	WSADATA wsa;
	SOCKET sock;
	SOCKADDR_IN server_addr;
	int retval;
public:
	m_Socket();
	~m_Socket();
	bool Initclient(u_short port, char *ip);
	SOCKET GetSocket() { return sock; }
};
m_Socket::m_Socket() {
	try {
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) throw - 1; //소켓초기화
	}
	catch (int i) {
		cout << "소켓 초기화 실패" << endl;
	}
	try {
		sock = socket(AF_INET, SOCK_STREAM, 0);   //클라이언트 쪽에서 사용할 소켓
		if (sock == NULL) throw sock;
	}
	catch (SOCKET err_sock) {
		cout << "Fail_sock()" << endl;
	}
	retval = 0;
}
m_Socket::~m_Socket() {
	closesocket(sock);
	WSACleanup();
}
bool m_Socket::Initclient(u_short port = 9000, char *ip = (char*)"127.0.0.1") {
	try {
		ZeroMemory(&server_addr, sizeof(server_addr)); //구조체를 비워준다.
		server_addr.sin_family = AF_INET; //4Byte 주소체계로 지정
		server_addr.sin_port = htons(port); //port를 네트워크바이트로 변환.
		server_addr.sin_addr.s_addr = inet_addr(ip);// IP 주소 도 네트워크 바이트로변환 로컬IP
		retval = connect(sock, (SOCKADDR*)&server_addr, sizeof(server_addr));//서버에 접속한다. 서버 Accept() 와 대응되는 함수이다.
		if (retval == SOCKET_ERROR) throw retval;							// 서버의 IP 와 서버가 지정한 port 에 지정해서 접속
	}
	catch (int err) { return false; }
	return true;
}
class Communication {			//서버와 클라이언트 데이터를 주고받기 위한 클래스
private:
	int retval;
	char buf[BUFSIZE];
	int share;
public:
	Communication();
	~Communication();
	bool Send(SOCKET cli_sock);
	bool Recive(SOCKET cli_sock);
};
Communication::Communication() {
	retval = 0;
	memset(buf, 0, sizeof(buf));
	share = 10;
}
Communication::~Communication() {

}
bool Communication::Send(SOCKET cli_sock) {  // 데이터를 보냄
	try {
		cin >> buf;
		int len = strlen(buf);
		if (buf[len - 1] == '\n') buf[len - 1] = '\0';
		retval = send(cli_sock, buf, strlen(buf), 0);
		if (retval == SOCKET_ERROR) throw retval;
	}
	catch (int err) {
		return false;
	}
	buf[retval] = '\0';
	cout << "보낸문자열:" << buf << endl;
	memset(buf, 0, sizeof(buf));
	return true;
}
bool Communication::Recive(SOCKET cli_sock) {  //데이터를 받음
	try {
		retval = recv(cli_sock, buf, sizeof(buf), 0);
		if (retval == SOCKET_ERROR) throw retval;
	}
	catch (int err) {
		return false;
	}
	if (retval == 0) return false;
	if (!strcmp(buf, "END")) return false;
	buf[retval] = '\0';
	cout << "받은문자열:" << buf << endl;
	memset(buf, 0, sizeof(buf));
	cout << "share : " << buf << endl;
	return true;
}
int main(void) {
	m_Socket *client = new m_Socket;
	client->Initclient();
	Communication *Data = new Communication;
	while (true) {
		if (!Data->Send(client->GetSocket())) break;
		if (!Data->Recive(client->GetSocket())) break;

	}
	delete client;
	return 0;
}