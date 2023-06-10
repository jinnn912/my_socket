#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32")

void errMsg(char* message);

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET servSock, clntSock;
	SOCKADDR_IN servAddr, clntAddr;

	int myClntAddr;
	char message[] = "Hello, mySocket";

	if (argc != 2)
	{
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) // ���� ���̺귯�� �ʱ�ȭ
	{
		errMsg("WSAStartup err");
	}

	// socket(), ���� ����
	servSock = socket(PF_INET, SOCK_STREAM, 0);
	if (servSock == INVALID_SOCKET)
	{
		errMsg("servSock socket err");
	}

	// bind(), IP�� PORT �Ҵ�
	memset(&servAddr, 0, sizeof(servAddr)); //
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(argv[1]));

	if (bind(servSock, (SOCKADDR *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		errMsg("bind err");
	}

	// listen(), ������ ������ ���� �������� ��
	if (listen(servSock, 5) == SOCKET_ERROR) // backlog : ���� ��û�� ����ų ����(���� ��� ���� ��), ��α�ť
	{
		errMsg("listen err");
	}

	myClntAddr = sizeof(clntAddr);
	// accept(), Ŭ���̾�Ʈ�� ��û ����
	clntSock = accept(servSock, (SOCKADDR *)&clntAddr, &myClntAddr);
	if (clntSock == INVALID_SOCKET)
	{
		errMsg("accept err");
	}

	// send(), ����� Ŭ���̾�Ʈ�� ������ ����
	send(clntSock, message, sizeof(message), 0);

	closesocket(clntSock);
	closesocket(servSock);
	WSACleanup();

	return 0;
}

void errMsg(char* message)
{
	printf("%s\n", message);
}