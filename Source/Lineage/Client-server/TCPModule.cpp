#include "TCPModule.h"
#include "CoreMinimal.h"
#include "TCPModule.h"

TCPModule::TCPModule() 
{
	// Initialize winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);

	if (wsOk != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't initialize winsock!"));
		return;
	}

	// Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't create socket, Err #")); // WSAGetLastError()
		WSACleanup();
		return;
	}

	// What server and what port we want to connect to
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	inet_pton(AF_INET, serverIP.c_str(), &server.sin_addr);

	// Connect to server
	int connResult = connect(sock, (sockaddr*)&server, sizeof(server));
	if (connResult == SOCKET_ERROR)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't connect to server, Err #")); // WSAGetLastError()
		closesocket(sock);
		WSACleanup();
		return;
	}
}


int TCPModule::Send(std::string buf)
{
	// size() + 1 because in C every string ends with 0 character
	return send(sock, buf.c_str(), buf.size() + 1, 0);
}

int TCPModule::Recv(char* buf)
{
	return recv(sock, buf, BUFFER_SIZE, 0);
}