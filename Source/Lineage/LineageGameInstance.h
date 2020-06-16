// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LoginSystem/LoginInterface.h"
#include "LineageGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LINEAGE_API ULineageGameInstance : public UGameInstance, public ILoginInterface
{
	GENERATED_BODY()

public:
	ULineageGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init();

	UFUNCTION(BlueprintCallable)
		void LoadLoginWidget();

	void LogIn(FString loginPass);

private:
	// We make a forward declaration of UUserWidget by writing "class" word before it
	TSubclassOf<class UUserWidget> LoginWidgetClass;
};
