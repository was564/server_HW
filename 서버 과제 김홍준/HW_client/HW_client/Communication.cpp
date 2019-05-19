#include "Communication.h"

void Communication::FirstSend()
{
	strcpy(buf, inet_ntoa(initialization::GetAddr()));

	// ������ ������
	retval = send(initialization::GetSock(), buf, strlen(buf), 0);
	if (retval == SOCKET_ERROR) {
		error::err_display("send()");
		exit(1);
	}
	len = retval;

	printf("[TCP Ŭ���̾�Ʈ] �ڽ��� IP %s %d����Ʈ�� ���½��ϴ�.\n", buf, retval);
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

	printf("[���� ������] %s, ", data);
	printf("share�� %s %d����Ʈ�� �޾ҽ��ϴ�.\n", &buf[len], retval);

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

	printf("[TCP Ŭ���̾�Ʈ] share�� %s %d����Ʈ�� ���½��ϴ�.\n", buf, retval);
}

void Communication::Send()
{
	// ������ �Է�
	printf("\n[���� ������] ");
	if (fgets(buf, BUFSIZE + 1, stdin) == NULL)
		exit(1);

	// '\n' ���� ����
	len = strlen(buf);
	if (buf[len - 1] == '\n')
		buf[len - 1] = '\0';
	if (strlen(buf) == 0)
		exit(1);

	// ������ ������
	retval = send(initialization::GetSock(), buf, strlen(buf), 0);
	if (retval == SOCKET_ERROR) {
		error::err_display("send()");
		exit(1);
	}
	printf("[TCP Ŭ���̾�Ʈ] %d����Ʈ�� ���½��ϴ�.\n", retval);
}

void Communication::Recv()
{
	// ������ �ޱ�
	retval = recv(initialization::GetSock(), buf, retval, 0);
	if (retval == SOCKET_ERROR) {
		error::err_display("recv()");
		exit(1);
	}
	else if (retval == 0)
		exit(1);

	// ���� ������ ���
	buf[retval] = '\0';
	printf("[TCP Ŭ���̾�Ʈ] %d����Ʈ�� �޾ҽ��ϴ�.\n", retval);
	printf("[���� ������] %s\n", buf);
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
