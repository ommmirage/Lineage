// Fill out your copyright notice in the Description page of Project Settings.

#include "LoginWidget.h"

#include "Components/Button.h"
#include "Components/EditableText.h"

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

void ULoginWidget::SetLoginInterface(ILoginInterface* _LoginInterface)
{
	this->LoginInterface = _LoginInterface;
}

void ULoginWidget::LogIn()
{
	FString login = LoginEditableText->GetText().ToString();
	FString pass = PassEditableText->GetText().ToString();

	FString loginPass = login + " " + pass;

	if (LoginInterface != nullptr)
	{
		LoginInterface->LogIn(loginPass);
	}
}