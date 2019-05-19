#include "Communication.h"

void Communication::FirstSend()
{
	strcpy(buf, inet_ntoa(initialization::GetAddr()));

	// 데이터 보내기
	retval = send(initialization::GetSock(), buf, strlen(buf), 0);
	if (retval == SOCKET_ERROR) {
		error::err_display("send()");
		exit(1);
	}
	len = retval;

	printf("[TCP 클라이언트] 자신의 IP %s %d바이트를 보냈습니다.\n", buf, retval);
}

void Communication::FirstRecv()
{
	retval = recv(initialization::GetSock(), buf, BUFSIZE, 0);
	if (retval == SOCKET_ERROR) {
		error::err_display("recv()");
		exit(1);
	}
	buf[retval] = '\0';
	strncpy(data, buf, len);
	data[len] = '\0';

	printf("[받은 데이터] %s, ", data);
	printf("share값 %s %d바이트를 받았습니다.\n", &buf[len], retval);

	share = atoi(&buf[len]);
	share += 10;
	memset(buf, '\0', sizeof(buf));
	_itoa(share, buf, 10);
}

void Communication::SecondSend()
{
	retval = send(initialization::GetSock(), buf, strlen(buf), 0);
	if (retval == SOCKET_ERROR) {
		error::err_display("send()");
		exit(1);
	}

	printf("[TCP 클라이언트] share값 %s %d바이트를 보냈습니다.\n", buf, retval);
}

void Communication::Send()
{
	// 데이터 입력
	printf("\n[보낼 데이터] ");
	if (fgets(buf, BUFSIZE + 1, stdin) == NULL)
		exit(1);

	// '\n' 문자 제거
	len = strlen(buf);
	if (buf[len - 1] == '\n')
		buf[len - 1] = '\0';
	if (strlen(buf) == 0)
		exit(1);

	// 데이터 보내기
	retval = send(initialization::GetSock(), buf, strlen(buf), 0);
	if (retval == SOCKET_ERROR) {
		error::err_display("send()");
		exit(1);
	}
	printf("[TCP 클라이언트] %d바이트를 보냈습니다.\n", retval);
}

void Communication::Recv()
{
	// 데이터 받기
	retval = recv(initialization::GetSock(), buf, retval, 0);
	if (retval == SOCKET_ERROR) {
		error::err_display("recv()");
		exit(1);
	}
	else if (retval == 0)
		exit(1);

	// 받은 데이터 출력
	buf[retval] = '\0';
	printf("[TCP 클라이언트] %d바이트를 받았습니다.\n", retval);
	printf("[받은 데이터] %s\n", buf);
}

Communication::Communication()
	:len(0), share(0)
{
	memset(buf, '\0', sizeof(buf));
	memset(data, '\0', sizeof(data));
}

Communication::~Communication()
{
}
