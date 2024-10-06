// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AttributeSets/PlayerAttributeSetBase.h"
#include "Net/UnrealNetwork.h"


void UPlayerAttributeSetBase::OnRep_BatteryCharge(const FGameplayAttributeData& OldBatteryCharge) 
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSetBase, BatteryCharge, OldBatteryCharge);
}


void UPlayerAttributeSetBase::OnRep_MaxBatteryCharge(const FGameplayAttributeData& OldMaxBatteryCharge)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSetBase, MaxBatteryCharge, OldMaxBatteryCharge);
}


void UPlayerAttributeSetBase::OnRep_BatteryChargeRegen(const FGameplayAttributeData& OldBatteryChargeRegen)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSetBase, BatteryChargeRegen, OldBatteryChargeRegen);
}


void UPlayerAttributeSetBase::OnRep_BatteryDrainFlashlight(const FGameplayAttributeData& OldBatteryDrainFlashlight)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSetBase, BatteryDrainFlashlight, OldBatteryDrainFlashlight);
}


void UPlayerAttributeSetBase::OnRep_BatteryDrainComms(const FGameplayAttributeData& OldBatteryDrainComms)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSetBase, BatteryDrainComms, OldBatteryDrainComms);
}


void UPlayerAttributeSetBase::OnRep_Stealthiness(const FGameplayAttributeData& OldStealthiness)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSetBase, Stealthiness, OldStealthiness);
}


void UPlayerAttributeSetBase::OnRep_PuzzleTimer(const FGameplayAttributeData& OldPuzzleTimer)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSetBase, PuzzleTimer, OldPuzzleTimer);
}


void UPlayerAttributeSetBase::OnRep_FloorEffectResistance(const FGameplayAttributeData& OldFloorEffectResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSetBase, FloorEffectResistance, OldFloorEffectResistance);
}


void UPlayerAttributeSetBase::OnRep_FlashlightSize(const FGameplayAttributeData& OldFlashlightSize)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSetBase, FlashlightSize, OldFlashlightSize);
}


void UPlayerAttributeSetBase::OnRep_MaxReviveCount(const FGameplayAttributeData& OldMaxReviveCount)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSetBase, MaxReviveCount, OldMaxReviveCount);
}


void UPlayerAttributeSetBase::OnRep_ReviveChance(const FGameplayAttributeData& OldReviveChance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSetBase, ReviveChance, OldReviveChance);
}


void UPlayerAttributeSetBase::OnRep_ReviveHealthPercent(const FGameplayAttributeData& OldReviveHealthPercent)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSetBase, ReviveHealthPercent, OldReviveHealthPercent);
}


void UPlayerAttributeSetBase::OnRep_ReviveBatteryPercent(const FGameplayAttributeData& OldReviveBatteryPercent)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSetBase, ReviveBatteryPercent, OldReviveBatteryPercent);
}

void UPlayerAttributeSetBase::OnRep_Gold(const FGameplayAttributeData& OldGold)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSetBase, Gold, OldGold);
}

void UPlayerAttributeSetBase::OnRep_Tokens(const FGameplayAttributeData& OldTokens)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSetBase, Tokens, OldTokens);
}

void UPlayerAttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSetBase, BatteryCharge, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSetBase, MaxBatteryCharge, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSetBase, BatteryChargeRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSetBase, BatteryDrainFlashlight, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSetBase, BatteryDrainComms, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSetBase, Stealthiness, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSetBase, PuzzleTimer, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSetBase, FloorEffectResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSetBase, FlashlightSize, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSetBase, MaxReviveCount, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSetBase, ReviveChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSetBase, ReviveHealthPercent, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSetBase, ReviveBatteryPercent, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSetBase, Gold, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSetBase, Tokens, COND_None, REPNOTIFY_Always);
}