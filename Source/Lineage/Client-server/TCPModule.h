#pragma once

#include <iostream>
#include <string>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define BUFFER_SIZE 4096


class TCPModule
{

public:
	TCPModule();

	int Send(std::string buf);

	int Recv(char* buf);

	// Server IP and listening port
	std::string serverIP = "127.0.0.1";
	int port = 54000;

	SOCKET sock;
	
};

