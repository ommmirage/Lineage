// Fill out your copyright notice in the Description page of Project Settings.


#include "LineagePlayerController.h"
#include "Kismet/GameplayStatics.h"



void ALineagePlayerController::SpawnCharacter(FString charLoadData)
{
	// Prepare data to load a character
	TArray<FString> charData;
	charLoadData.ParseIntoArray(charData, TEXT(" "), true);
	FString nick = charData[1];
	float x = FCString::Atof(*charData[2]);
	float y = FCString::Atof(*charData[3]);
	float z = FCString::Atof(*charData[4]);

	FActorSpawnParameters SpawnParams;
	Char = GetWorld()->SpawnActor<ACharacterBase>(
		CharacterToSpawn,
		FVector(x, y, z),
		FRotator(),
		SpawnParams
		);
	Possess(Char);
}

void ALineagePlayerController::GetInventoryData()
{
	if (Char == nullptr) return;

}
