// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DungeonPlayerController.h"
#include "Player/DungeonPlayerState.h"
#include "AbilitySystemComponent.h"

void ADungeonPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ADungeonPlayerState* PS = GetPlayerState<ADungeonPlayerState>();
	if (PS)
	{
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
	}
}
