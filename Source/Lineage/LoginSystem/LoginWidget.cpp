// Fill out your copyright notice in the Description page of Project Settings.

#include "LoginWidget.h"

#include "Components/Button.h"

bool ULoginWidget::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(LogInBtn != nullptr)) return false;
	LogInBtn->OnClicked.AddDynamic(this, &ULoginWidget::LogIn);

	return true;
}

void ULoginWidget::LogIn()
{
	UE_LOG(LogTemp, Warning, TEXT("Logging in."));
}