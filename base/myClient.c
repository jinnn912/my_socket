#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32")

void errMsg(char* message);

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET mySocket;
	SOCKADDR_IN servAddr;

	char message[30];
	int strLen = 0;

	if (argc != 3)
	{
		printf("Usage: %s <ip> <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		errMsg("WSAStartup err");
	}

	// socket()
	mySocket = socket(PF_INET, SOCK_STREAM, 0);
	if (mySocket == INVALID_SOCKET)
	{
		errMsg("socket err");
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	servAddr.sin_port = htons(atoi(argv[2]));

	// connect()
	if (connect(mySocket, (SOCKADDR *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		errMsg("connect err");
	}

	// recv(), 서버로부터 전송된 데이터를 수신함(읽어옴)
	strLen = recv(mySocket, message, sizeof(message) - 1, 0);
	if (strLen == -1)
	{
		errMsg("read err");
	}
	else
	{
		printf("Message from server : %s\n", message);
	}

	closesocket(mySocket);
	WSACleanup();

	return 0;
}

void errMsg(char* message)
{
	printf("%s\n", message);
}