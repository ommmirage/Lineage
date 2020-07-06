// Fill out your copyright notice in the Description page of Project Settings.

#include "LineageGameInstance.h"

#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "LineagePlayerController.h"
#include "Templates/Casts.h"

#include "LoginSystem/LoginWidget.h"

#include <iostream>
#include <string>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define BUFFER_SIZE 4096

ULineageGameInstance::ULineageGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> LoginWidgetBPClass(TEXT("/Game/UI/WBP_Login"));
	if (!ensure(LoginWidgetBPClass.Class != nullptr)) return;
	LoginWidgetClass = LoginWidgetBPClass.Class;
}

void ULineageGameInstance::ULineageGameInstance::Init()
{
}

void ULineageGameInstance::LoadLoginWidget()
{
	ULoginWidget* LoginWidget = CreateWidget<ULoginWidget>(this, LoginWidgetClass);
	if (!ensure(LoginWidget != nullptr)) return;

	LoginWidget->AddToViewport();

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(LoginWidget->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;

	LoginWidget->SetLoginInterface(this);
}

void ULineageGameInstance::LogIn(FString loginPass)
{
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
				// Gets character data if login and password is right
				// Gets "" otherwise
				std::string character = std::string(buf, 0, bytesReceived);
				FString charLoadData(character.c_str());
				if (character.length() == 0)
				{
					UE_LOG(LogTemp, Warning, TEXT("Wrong username or password."));
				}
				else
				{
					ALineagePlayerController* LineagePlayerController = Cast<ALineagePlayerController>(GetFirstLocalPlayerController());
					LineagePlayerController->bShowMouseCursor = true;
					FInputModeGameOnly InputModeData;
					LineagePlayerController->SetInputMode(InputModeData);
					//UE_LOG(LogTemp, Warning, TEXT("charLoadData: %s"), charLoadData);
					UGameplayStatics::OpenLevel(this, "Main", true, charLoadData);
				}
			}
		}
	}

	WSACleanup();
}

void ULineageGameInstance::LoadObjects()
{

}
