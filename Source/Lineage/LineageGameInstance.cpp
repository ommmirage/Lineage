// Fill out your copyright notice in the Description page of Project Settings.

#include "LineageGameInstance.h"

#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

#include "LoginSystem/LoginWidget.h"

ULineageGameInstance::ULineageGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> LoginWidgetBPClass(TEXT("/Game/Login/WBP_Login"));
	if (!ensure(LoginWidgetBPClass.Class != nullptr)) return;
	LoginWidgetClass = LoginWidgetBPClass.Class;
}

void ULineageGameInstance::ULineageGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *LoginWidgetClass->GetName());
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

void ULineageGameInstance::ULineageGameInstance::LogIn()
{

}