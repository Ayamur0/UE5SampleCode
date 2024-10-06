// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AttributeSets/CharacterAttributeSetBase.h"
#include "PlayerAttributeSetBase.generated.h"

/**
 * 
 */
UCLASS()
class PROMETHEUS_API UPlayerAttributeSetBase : public UCharacterAttributeSetBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battery", ReplicatedUsing = OnRep_BatteryCharge)
	FGameplayAttributeData BatteryCharge;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSetBase, BatteryCharge)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battery", ReplicatedUsing = OnRep_MaxBatteryCharge)
	FGameplayAttributeData MaxBatteryCharge;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSetBase, MaxBatteryCharge)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battery", ReplicatedUsing = OnRep_BatteryChargeRegen)
	FGameplayAttributeData BatteryChargeRegen;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSetBase, BatteryChargeRegen)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battery", ReplicatedUsing = OnRep_BatteryDrainFlashlight)
	FGameplayAttributeData BatteryDrainFlashlight;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSetBase, BatteryDrainFlashlight)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battery", ReplicatedUsing = OnRep_BatteryDrainComms)
	FGameplayAttributeData BatteryDrainComms;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSetBase, BatteryDrainComms)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", ReplicatedUsing = OnRep_Stealthiness)
	FGameplayAttributeData Stealthiness;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSetBase, Stealthiness)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Misc", ReplicatedUsing = OnRep_PuzzleTimer)
	FGameplayAttributeData PuzzleTimer;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSetBase, PuzzleTimer)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Misc", ReplicatedUsing = OnRep_FloorEffectResistance)
	FGameplayAttributeData FloorEffectResistance;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSetBase, FloorEffectResistance)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Misc", ReplicatedUsing = OnRep_FlashlightSize)
	FGameplayAttributeData FlashlightSize;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSetBase, FlashlightSize)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Revive", ReplicatedUsing = OnRep_MaxReviveCount)
	FGameplayAttributeData MaxReviveCount;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSetBase, MaxReviveCount)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Revive", ReplicatedUsing = OnRep_ReviveChance)
	FGameplayAttributeData ReviveChance;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSetBase, ReviveChance)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Revive", ReplicatedUsing = OnRep_ReviveHealthPercent)
	FGameplayAttributeData ReviveHealthPercent;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSetBase, ReviveHealthPercent)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Revive", ReplicatedUsing = OnRep_ReviveBatteryPercent)
	FGameplayAttributeData ReviveBatteryPercent;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSetBase, ReviveBatteryPercent)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Currency", ReplicatedUsing = OnRep_Gold)
	FGameplayAttributeData Gold;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSetBase, Gold)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Currency", ReplicatedUsing = OnRep_Tokens)
	FGameplayAttributeData Tokens;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSetBase, Tokens)

	UFUNCTION()
	virtual void OnRep_BatteryCharge(const FGameplayAttributeData& OldBatteryCharge);

	UFUNCTION()
	virtual void OnRep_MaxBatteryCharge(const FGameplayAttributeData& OldMaxBatteryCharge);

	UFUNCTION()
	virtual void OnRep_BatteryChargeRegen(const FGameplayAttributeData& OldBatteryChargeRegen);

	UFUNCTION()
	virtual void OnRep_BatteryDrainFlashlight(const FGameplayAttributeData& OldBatteryDrainFlashlight);

	UFUNCTION()
	virtual void OnRep_BatteryDrainComms(const FGameplayAttributeData& OldBatteryDrainComms);

	UFUNCTION()
	virtual void OnRep_Stealthiness(const FGameplayAttributeData& OldStealthiness);

	UFUNCTION()
	virtual void OnRep_PuzzleTimer(const FGameplayAttributeData& OldPuzzleTimer);

	UFUNCTION()
	virtual void OnRep_FloorEffectResistance(const FGameplayAttributeData& OldFloorEffectResistance);

	UFUNCTION()
	virtual void OnRep_FlashlightSize(const FGameplayAttributeData& OldFlashlightSize);

	UFUNCTION()
	virtual void OnRep_MaxReviveCount(const FGameplayAttributeData& OldMaxReviveCount);

	UFUNCTION()
	virtual void OnRep_ReviveChance(const FGameplayAttributeData& OldReviveChance);

	UFUNCTION()
	virtual void OnRep_ReviveHealthPercent(const FGameplayAttributeData& OldReviveHealthPercent);

	UFUNCTION()
	virtual void OnRep_ReviveBatteryPercent(const FGameplayAttributeData& OldReviveBatteryPercent);

	UFUNCTION()
	virtual void OnRep_Gold(const FGameplayAttributeData& OldGold);

	UFUNCTION()
	virtual void OnRep_Tokens(const FGameplayAttributeData& OldTokens);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
