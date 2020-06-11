#pragma once
#include "TCPListener.h"

class MultiClientListener : public TCPListener
{
public:

	MultiClientListener(const char* ipAddress, int port) :
		TCPListener(ipAddress, port)
	{

	}

protected:

	// Handler for client connections
	void onClientConnected(int clientSocket);

	// Handler for client disconnections
	void onClientDisconnected(int clientSocket);

	void onMessageReceived(int sock, const char* msg, int bytesIn);
};

