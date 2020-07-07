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

	UFUNCTION(BlueprintCallable)
		void SpawnCharacter(FString charLoadData);

private:
	ACharacterBase* Char = nullptr;

};
