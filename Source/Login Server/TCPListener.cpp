#include "TCPListener.h"

TCPListener::TCPListener(const char* ipAddress, int port) :
	m_ipAddress(ipAddress), m_port(port)
{

}

int TCPListener::init()
{
	// Initialize winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		return wsOk;
	}

	// Create a socket
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET)
	{
		return WSAGetLastError();
	}

	// Bind the IP address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(m_port);
	inet_pton(AF_INET, m_ipAddress, &hint.sin_addr);

	if (bind(m_socket, (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR)
	{
		return WSAGetLastError();
	}

	// Tell Winsock the socket is for listening
	if (listen(m_socket, SOMAXCONN) == SOCKET_ERROR)
	{
		return WSAGetLastError();
	}

	// Zero the master file descriptor
	FD_ZERO(&m_master);

	// Add our first socket that we're interested in interacting with; the listening socket
	// It's important that this socket is added for our server or else 
	// we won't hear incoming connections
	FD_SET(m_socket, &m_master);

	return 0;
}

int TCPListener::run()
{
	bool running = true;

	while (running)
	{
		fd_set copy = m_master;

		// Sockets that are interacting with the server are returned.
		// If noone is interacting it will wait until some socket interacts.
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		// Loop through all the current connections / potential connect
		for (int i = 0; i < socketCount; i++)
		{
			SOCKET sock = copy.fd_array[i];

			// Is it an inbound communication?
			if (sock == m_socket)
			{
				// Accept a new connection
				sockaddr_in clientAddr;
				int clientSize = sizeof(clientAddr);
				SOCKET clientSocket = accept(m_socket, (sockaddr*)&clientAddr, &clientSize);

				// Add the new connection to the list of connected clients
				FD_SET(clientSocket, &m_master);

				// Send a welcome message to the connected client
				//std::string welcomeMsg = "Welcome to the server!";
				//send(clientSocket, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);

				// Client connected
				onClientConnected(clientSocket);
			}
			else // It's an inbound message
			{
				char buf[BUFFER_SIZE];
				ZeroMemory(buf, BUFFER_SIZE);

				// Receive message
				int bytesIn = recv(sock, buf, BUFFER_SIZE, 0);
				if (bytesIn <= 0)
				{
					// Drop the client
					onClientDisconnected(sock);
					closesocket(sock);
					FD_CLR(sock, &m_master);
				}
				else
				{
					onMessageReceived(sock, buf, bytesIn);
					//send(sock, )
					//for (int i = 0; i < master.fd_count; i++)
					//{
					//	SOCKET outSock = master.fd_array[i];
					//	if (outSock != listening && outSock != sock)
					//	{
					//		send(outSock, buf, bytesIn, 0);
					//	}
					//}
				}
			}
		}
	}

	// Remove the listening socket from the master file descriptor set
	// and close it to prevent anyone else trying to connect
	FD_CLR(m_socket, &m_master);
	closesocket(m_socket);

	// Message to the users that server is shutting down
	std::string msg = "Server is shutting down.\n";

	while (m_master.fd_count > 0)
	{
		SOCKET sock = m_master.fd_array[0];
		send(sock, msg.c_str(), msg.size() + 1, 0);
		FD_CLR(sock, &m_master);
		closesocket(sock);
	}

	// Cleanup winsock
	WSACleanup();
	return 0;
}

// Handler for client connections
void TCPListener::onClientConnected(int clientSocket)
{

}

// Handler for client disconnections
void TCPListener::onClientDisconnected(int clientSocket)
{

}

void TCPListener::onMessageReceived(int sock, const char* msg, int bytesIn)
{
}

void TCPListener::sendToClient(int clientSocket, std::string msg)
{
	send(clientSocket, msg.c_str(), msg.size() + 1, 0);
}