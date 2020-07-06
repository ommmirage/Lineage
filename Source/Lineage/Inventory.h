// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Items/MasterItem.h"
#include "Inventory.generated.h"

USTRUCT()
struct FSlot {

    GENERATED_USTRUCT_BODY()
       
	AMasterItem* Item;
    int Amount;

};

UCLASS()
class LINEAGE_API AInventory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	

};
