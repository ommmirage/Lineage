#pragma once
#include "TCPListener.h"
#include "Database.h"

class MultiClientListener : public TCPListener
{
public:

	MultiClientListener(const char* ipAddress, int port) :
		TCPListener(ipAddress, port)
	{

	}

	Database db;

protected:

	// Handler for client connections
	void onClientConnected(int clientSocket);

	// Handler for client disconnections
	void onClientDisconnected(int clientSocket);

	void onMessageReceived(int sock, const char* msg, int bytesIn);
};

