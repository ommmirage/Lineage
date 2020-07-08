// Fill out your copyright notice in the Description page of Project Settings.


#include "LineagePlayerController.h"
#include "Kismet/GameplayStatics.h"

#include "Structs/Slot.h"

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

	// Load inventory
	// i = 5 because float z = FCString::Atof(*charData[4]);
	for (int i = 5; i < charData.Num(); i += 3)
	{
		FSlot s;
		s.objectId = FCString::Atoi(*charData[i]);
		s.itemId = FCString::Atoi(*charData[i + 1]);
		s.amount = FCString::Atoi(*charData[i + 2]);
		Char->slots.Add(s);
	}

	// Set input mode
	FInputModeGameAndUI InputModeData;
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	bShowMouseCursor = true;
}
