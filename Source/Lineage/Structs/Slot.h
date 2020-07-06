#pragma once

#include "../Items/MasterItem.h"
#include "Slot.generated.h"

USTRUCT()
struct FSlot {

	GENERATED_USTRUCT_BODY()

	AMasterItem* Item;
	int Amount;

};