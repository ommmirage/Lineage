// Fill out your copyright notice in the Description page of Project Settings.

#include "LineageGameInstance.h"

#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "LineagePlayerController.h"
#include "Templates/Casts.h"

#include "LoginSystem/LoginWidget.h"

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
	// Send and receive data
	if (loginPass.Len() > 1)
	{
		std::string loginPassCpp = std::string(TCHAR_TO_UTF8(*loginPass));
		int sendResult = TCP.Send(loginPassCpp);
		if (sendResult != SOCKET_ERROR)
		{
			// Wait for response
			char buf[BUFFER_SIZE];
			ZeroMemory(buf, BUFFER_SIZE);
			int bytesReceived = TCP.Recv(buf);
			if (bytesReceived > 0)
			{
				// Gets character data if login and password is right
				// Gets "" otherwise
				std::string character = std::string(buf, 0, bytesReceived);
				FString charData(character.c_str());
				if (character.length() == 0)
				{
					UE_LOG(LogTemp, Warning, TEXT("Wrong username or password."));
				}
				else
				{
					onCharDataReceived(charData);
				}
			}
		}
	}

	WSACleanup();
}

void ULineageGameInstance::onCharDataReceived(FString charData)
{
	ALineagePlayerController* LineagePlayerController = Cast<ALineagePlayerController>(GetFirstLocalPlayerController());
	LineagePlayerController->bShowMouseCursor = true;
	FInputModeGameOnly InputModeData;
	LineagePlayerController->SetInputMode(InputModeData);
	UGameplayStatics::OpenLevel(this, "Main", true, charData);
}


void ULineageGameInstance::LoadObjects()
{

}
