// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Characters/CharacterBase.h"
#include "LineagePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LINEAGE_API ALineagePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Load Character")
		TSubclassOf<APawn> CharacterToSpawn;

	void LoadCharacter(FString charLoadData);

	UFUNCTION(BlueprintCallable)
	void SpawnCharacter();

private:
	ACharacterBase* Char = nullptr;

};
