// Fill out your copyright notice in the Description page of Project Settings.


#include "LineagePlayerController.h"
#include "LineageGameInstance.h" // TODO get rid of double inheritance

void ALineagePlayerController::BeginPlay()
{
	Super::BeginPlay();
	//LevelLoaded();
	UE_LOG(LogTemp, Warning, TEXT("Lineage Player Conroller BeginPlay()."))
}
