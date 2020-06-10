// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LineageGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LINEAGE_API ULineageGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	ULineageGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init();

	UFUNCTION(BlueprintCallable)
		void LoadLoginWidget();

private:
	// We make a forward declaration of UUserWidget by writing "class" word before it
	TSubclassOf<class UUserWidget> LoginWidgetClass;
};
