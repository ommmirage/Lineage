#pragma once

#include "Slot.generated.h"

USTRUCT(BlueprintType)
struct FSlot {

	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
		int objectId;

	UPROPERTY(BlueprintReadWrite)
		int itemId;

	UPROPERTY(BlueprintReadWrite)
		int amount;

};