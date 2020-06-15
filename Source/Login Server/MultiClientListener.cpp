#include "MultiClientListener.h"
#include <string>

#include "Database.h"

Database db;

// Handler for client connections
void MultiClientListener::onClientConnected(int clientSocket)
{
	std::cout << "Client with socket #" << clientSocket << " connected." << std::endl;
}

// Handler for client disconnections
void MultiClientListener::onClientDisconnected(int clientSocket)
{
	std::cout << "Client with socket #" << clientSocket << " disconnected." << std::endl;
}

void MultiClientListener::onMessageReceived(int sock, const char* msg, int bytesIn)
{
	//std::cout << std::string(msg, 0, bytesIn) << std::endl;
	std::string login = db.checkLoginPassword(msg);
	if (login.length() > 0)
	{
		std::cout << "Client entered right login and password!" << std::endl;
		std::string character = db.getCharacter(login);
		sendToClient(sock, "character");
	}
	else
	{
		std::cout << "Client entered wrong details." << std::endl;
		sendToClient(sock, "Wrong username or password.");
	}
}