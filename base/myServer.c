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

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) // 소켓 라이브러리 초기화
	{
		errMsg("WSAStartup err");
	}

	// socket(), 소켓 생성
	servSock = socket(PF_INET, SOCK_STREAM, 0);
	if (servSock == INVALID_SOCKET)
	{
		errMsg("servSock socket err");
	}

	// bind(), IP와 PORT 할당
	memset(&servAddr, 0, sizeof(servAddr)); //
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(argv[1]));

	if (bind(servSock, (SOCKADDR *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		errMsg("bind err");
	}

	// listen(), 생성한 소켓을 서버 소켓으로 함
	if (listen(servSock, 5) == SOCKET_ERROR) // backlog : 연결 요청을 대기시킬 공간(연결 대기 제한 수), 백로그큐
	{
		errMsg("listen err");
	}

	myClntAddr = sizeof(clntAddr);
	// accept(), 클라이언트의 요청 수락
	clntSock = accept(servSock, (SOCKADDR *)&clntAddr, &myClntAddr);
	if (clntSock == INVALID_SOCKET)
	{
		errMsg("accept err");
	}

	// send(), 연결된 클라이언트로 데이터 전송
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