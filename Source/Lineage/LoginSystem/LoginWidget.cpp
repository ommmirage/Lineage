// Fill out your copyright notice in the Description page of Project Settings.

#include "LoginWidget.h"

#include "Components/Button.h"
#include "Components/EditableText.h"

#include <iostream>
#include <string>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define BUFFER_SIZE 4096

bool ULoginWidget::Initialize()
{
	// Initialize widget
	bool Success = Super::Initialize();
	if (!Success) return false;

	// LogInBtn Callback
	if (!ensure(LogInBtn != nullptr)) return false;
	LogInBtn->OnClicked.AddDynamic(this, &ULoginWidget::LogIn);

	return true;
}

void ULoginWidget::LogIn()
{
	if (LoginInterface != nullptr)
	{
		LoginInterface->LogIn();
	}
	// Server IP and listening port
	std::string serverIP = "127.0.0.1";
	int port = 54000;

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
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
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

	// Send and receive data
	char buf[BUFFER_SIZE];
	FString login = LoginEditableText->GetText().ToString();
	FString pass = PassEditableText->GetText().ToString();

	FString loginPass = login + " " + pass;

	if (loginPass.Len() > 1)
	{
		std::string loginPassCpp = std::string(TCHAR_TO_UTF8(*loginPass));
		int sendResult = send(sock, loginPassCpp.c_str(), loginPassCpp.size() + 1, 0);
		// size() + 1 because in C every string ends with 0 character
		if (sendResult != SOCKET_ERROR)
		{
			// Wait for response
			ZeroMemory(buf, BUFFER_SIZE);
			int bytesReceived = recv(sock, buf, BUFFER_SIZE, 0);
			if (bytesReceived > 0)
			{
				// Sends character data if login and password is right
				// Sends "" otherwise
				std::string character = std::string(buf, 0, bytesReceived);
				FString FScharacter(character.c_str());
				if (character.length() == 0)
				{
					UE_LOG(LogTemp, Warning, TEXT("Wrong username or password."));
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("%s"), *FScharacter);
					//GetWorld()->GetGameInstance()->LoadCharacter();
				}
			}
		}
	}

	WSACleanup();
}