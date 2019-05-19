#define _CRT_SECURE_NO_WARNINGS         // 최신 VC++ 컴파일 시 경고 방지
#define _WINSOCK_DEPRECATED_NO_WARNINGS // 최신 VC++ 컴파일 시 경고 방지
#include<iostream>
#include<WinSock2.h>
#include<stdlib.h>
#include<time.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
#define BUFSIZE 1024
class m_Socket {
private:
	WSADATA wsa;
	SOCKET sock;
	SOCKADDR_IN serveraddr;
	int retval;
public:
	m_Socket();
	~m_Socket();
	bool initserver(u_short port, char *ip);
	bool listen_client();
	SOCKET Getserv_sock() { return sock; }
};
m_Socket::m_Socket() {// 윈속과 서버에서 사용할 소켓 초기화
	try {
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) throw - 1; //소켓초기화
	}
	catch (int i) {
		cout << "소켓 초기화 실패" << endl;
	}
	try {
		sock = socket(AF_INET, SOCK_STREAM, 0);   //서버쪽에서 사용할 소켓
		if (sock == INVALID_SOCKET) throw sock;
	}
	catch (SOCKET err_sock) {
		cout << "Fail_sock()" << endl;
	}

}
m_Socket::~m_Socket() {
	closesocket(sock);
	WSACleanup();
}
bool m_Socket::initserver(u_short port = 9000, char *ip = (char*)"127.0.0.1") { //디폴트값일때 기본 디폴트 주소값이 들어간다.
	ZeroMemory(&serveraddr, sizeof(serveraddr)); //구조체를 비워준다.
	serveraddr.sin_family = AF_INET; //4Byte 주소체계로 지정
	serveraddr.sin_port = htons(port); //port를 네트워크바이트로 변환.
	serveraddr.sin_addr.s_addr = inet_addr(ip);// IP 주소 도 네트워크 바이트로변환 로컬IP
	retval = bind(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));// 사용할 sock에 정보를 씌어준다. 즉 커널에 등록
																  //성공시 0 반환
	if (retval == SOCKET_ERROR) {//실패시 -1 반환 SOCKET_ERROR 대신 -1 사용가능
		cout << "bind() Fail";
		return false;
	}
	return true;
}
bool m_Socket::listen_client() {
	retval = listen(sock, SOMAXCONN);
	if (retval == INVALID_SOCKET) return false;
	return true;
}
class accept_client {           //접속만 받아주는 클래스
private:
	char *pStr;
	FILE *fp;
	int retval;
	SOCKET client_sock;        //클라이언트와 서버가 서로 데이터를 주고받을 수 있게 만들어주는 소켓 이다.
	SOCKADDR_IN client_addr;   //현재 접속하는 클라이언트의 주소를 저장하는 변수이다.
	int addr_len;
public:
	accept_client();
	~accept_client();
	bool Accept_func(SOCKET serv_sock);
	void impo();
	SOCKET GetSocket() { return client_sock; }
};
accept_client::accept_client() {
	addr_len = sizeof(client_addr);           // 클라이언트 주소 구조체의 크기를 저장합니다.
	retval = 0;
}
accept_client::~accept_client() {
	impo();
	//closesocket(client_sock);

}
bool accept_client::Accept_func(SOCKET serv_sock) {

	try {

		client_sock = accept(serv_sock, (SOCKADDR*)&client_addr, &addr_len); //클라이언트 접속만 담당하는 함수
		if (client_sock == INVALID_SOCKET) throw false;                     //접속을 실패시 err 이므로 false를 넘겨줍니다.
	}
	catch (bool err) { return err; }
	
	fp = fopen("log.dot", "w");										//파일 쓰기/읽기/생성 가능 한 함수.
	fclose(fp);
	impo();															//접속 결과로 클라이언트의 포트값과 IP 주소값을 보여줍니다.

	return true;
}
void accept_client::impo() {
	fp = fopen("log.dot", "r");
	cout << "IP주소:" << inet_ntoa(client_addr.sin_addr) << endl; // 네트워크 를 호스트로 변경
	cout << "포트번호:" << ntohs(client_addr.sin_port) << endl;  // 네트워크 를 호스트로 변경
	fclose(fp);
}
class Communication {  // 서버와 클라이언트 간에 데이터를 주고받는 클래스
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
bool Communication::Send(SOCKET cli_sock) { //클라이언트에게 보낼 문자
	try {
		retval = send(cli_sock, buf, BUFSIZE, 0);     //서버가 클라이언트에게 데이터를 보내는 함수 입니다.
		if (retval == SOCKET_ERROR) throw retval;
	}
	catch (int err) {
		return false;
	}
	buf[retval] = '\0';
	cout << "보낸문자열:" << buf << endl;
	if (!strcmp(buf, "END")) return false;
	memset(buf, 0, sizeof(buf));
	cout << "share 값: " << buf << endl;
	return true;
	
	
}
bool Communication::Recive(SOCKET cli_sock) {
	try {
		memset(buf, 0, sizeof(buf));
		retval = recv(cli_sock, buf, BUFSIZE, 0);   //서버가 클라이언트로부터 데이터를 받는 함수 입니다.
		if (retval == SOCKET_ERROR) throw retval;
	}
	catch (int err) {
		return false;
	}

	buf[retval] = '\0';
	cout << "받은문자열:" << buf << endl;

	return true;
}
int main(void) {
	m_Socket *server = new m_Socket;
	if (!server->initserver()) return 0;
	if (!server->listen_client()) return 0;
	accept_client *client = new accept_client;
	Communication *Data = new Communication;
	while (true) {
		if (!client->Accept_func(server->Getserv_sock())) {
			cout << "Fail Accept()" << endl;
			continue;
		}
		while (true) {

			if (!Data->Recive(client->GetSocket())) break;  //recv() 함수가 데이터를 받지못하면 반복문이 종료됩니다.
			if (!Data->Send(client->GetSocket())) break;    //END를 받거나 send를 하지못하면 실패함으로 반복문이 종료됩니다.

		}

	}
	delete Data;
	delete client;
	delete server;



	return 0;
}