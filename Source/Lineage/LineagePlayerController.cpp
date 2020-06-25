// Fill out your copyright notice in the Description page of Project Settings.


#include "LineagePlayerController.h"
//#include "LineageGameInstance.h" // TODO get rid of double inheritance
#include "Kismet/GameplayStatics.h"

void ALineagePlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("LineagePlayerConroller is running"));
}

void ALineagePlayerController::LoadCharacter(FString charLoadData)
{
	// Prepare data to load a character
	TArray<FString> charData;
	charLoadData.ParseIntoArray(charData, TEXT(" "), true);
	FString nick = charData[1];
	float x = FCString::Atof(*charData[2]);
	float y = FCString::Atof(*charData[3]);
	float z = FCString::Atof(*charData[4]);
	FVector location = FVector(x, y, z);
	UE_LOG(LogTemp, Warning, TEXT("%s, %f, %f, %f"), *nick, x, y, z);

	// Set game input mode
	//APlayerController* PlayerController = GetFirstLocalPlayerController();
	//PlayerController->bShowMouseCursor = true;
	//FInputModeGameOnly InputModeData;
	//PlayerController->SetInputMode(InputModeData);

	//UGameplayStatics::OpenLevel(this, "Main", true);

	//// Spawn a character
	//FActorSpawnParameters SpawnParams;

	//GetWorld()->SpawnActor<APawn>(CharacterToSpawn, location, FRotator(), SpawnParams);
}
