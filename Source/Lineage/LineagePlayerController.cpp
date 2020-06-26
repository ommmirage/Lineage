// Fill out your copyright notice in the Description page of Project Settings.


#include "LineagePlayerController.h"
#include "Kismet/GameplayStatics.h"


void ALineagePlayerController::LoadCharacter(FString charLoadData)
{
	
	// Prepare data to load a character
	TArray<FString> charData;
	charLoadData.ParseIntoArray(charData, TEXT(" "), true);
	FString nick = charData[1];
	float x = FCString::Atof(*charData[2]);
	float y = FCString::Atof(*charData[3]);
	float z = FCString::Atof(*charData[4]);

	//Char = new ACharacterBase();
	//Char->location = FVector(x, y, z);

	//UE_LOG(LogTemp, Warning, TEXT("%s, %f, %f, %f"), *nick, Char->location.X, y, z);

	//Set game input mode
	//bShowMouseCursor = true;
	//FInputModeGameOnly InputModeData;
	//SetInputMode(InputModeData);

	UGameplayStatics::OpenLevel(this, "Main", true);
}

void ALineagePlayerController::SpawnCharacter()
{
	if (Char != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Char->location.x: %f"), Char->location.X);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Char == nullptr"));
	}
	FActorSpawnParameters SpawnParams;
	Possess(GetWorld()->SpawnActor<APawn>(
		CharacterToSpawn,
		FVector(0.f, 0.f, 400.f),
		FRotator(),
		SpawnParams
		));
}
