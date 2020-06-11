#pragma once

#include <iostream>
#include <WS2tcpip.h>
#include <string>

#pragma comment (lib, "ws2_32.lib")

#define BUFFER_SIZE 4096 

class TCPListener
{
public:

	TCPListener(const char* ipAddress, int port);

	// Initialize the listener
	int init();

	// Run the listener
	int run();

protected: // У дочерних классов есть доступ к родительскому, у других - нет

	// Handler for client connections
	virtual void onClientConnected(int clientSocket);

	// Handler for client disconnections
	virtual void onClientDisconnected(int clientSocket);

	virtual void onMessageReceived(int sock, const char* msg, int bytesIn);

	void sendToClient(int clientSocket, std::string msg);

private:
	const char* m_ipAddress;	// IP Address server will run on
	int			m_port;			// Port # for the web service
	int			m_socket;		// Internal socket File Descriptor (fd)
								// for the listening socket
	fd_set		m_master;		// Master file descriptor set

};

