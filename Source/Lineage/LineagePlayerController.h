// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LineagePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LINEAGE_API ALineagePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay();
};
