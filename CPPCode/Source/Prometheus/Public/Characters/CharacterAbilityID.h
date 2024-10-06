#pragma once

#include "CoreMinimal.h"
#include "CharacterAbilityID.generated.h"

UENUM(BlueprintType)
enum class ECharacterAbilityID : uint8
{
	None UMETA(DisplayName = "None"),
	Confirm UMETA(DisplayName = "Confirm"),
	Cancel UMETA(DisplayName = "Cancel"),
};