// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "DungeonPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PROMETHEUS_API ADungeonPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ADungeonPlayerState();

	// Implement IAbilitySystemInterface
	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	TObjectPtr<class UPlayerAttributeSetBase> GetAttributeSetBase() const;

	UFUNCTION(BlueprintCallable, Category = "Player State")
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "Player State|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Player State|Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Player State|Attributes")
	float GetHealthRegen() const;

	UFUNCTION(BlueprintCallable, Category = "Player State|Attributes")
	float GetStamina() const;

	UFUNCTION(BlueprintCallable, Category = "Player State|Attributes")
	float GetMaxStamina() const;

	UFUNCTION(BlueprintCallable, Category = "Player State|Attributes")
	float GetStaminaRegen() const;

	UFUNCTION(BlueprintCallable, Category = "Player State|Attributes")
	float GetWalkSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "Player State|Attributes")
	float GetDamageReduction() const;

	UFUNCTION(BlueprintCallable, Category = "Player State|Attributes")
	float GetCooldownReduction() const;

	UFUNCTION(BlueprintCallable, Category = "Player State|Attributes")
	float GetBatteryCharge() const;

	UFUNCTION(BlueprintCallable, Category = "Player State|Attributes")
	float GetMaxBatteryCharge() const;

	UFUNCTION(BlueprintCallable, Category = "Player State|Attributes")
	float GetBatteryChargeRegen() const;

	UFUNCTION(BlueprintCallable, Category = "Player State|Attributes")
	float GetBatteryDrainFlashlight() const;

	UFUNCTION(BlueprintCallable, Category = "Player State|Attributes")
	float GetBatteryDrainComms() const;

	UFUNCTION(BlueprintCallable, Category = "Player State|Attributes")
	float GetStealthiness() const;

	UFUNCTION(BlueprintCallable, Category = "Player State|Attributes")
	float GetPuzzleTimer() const;

	UFUNCTION(BlueprintCallable, Category = "Player State|Attributes")
	float GetFloorEffectResistance() const;

	UFUNCTION(BlueprintCallable, Category = "Player State|Attributes")
	float GetFlashlightSize() const;

	UFUNCTION(BlueprintCallable, Category = "Player State|Attributes")
	float GetMaxReviveCount() const;

	UFUNCTION(BlueprintCallable, Category = "Player State|Attributes")
	float GetReviveChance() const;

	UFUNCTION(BlueprintCallable, Category = "Player State|Attributes")
	float GetReviveHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "Player State|Attributes")
	float GetReviveBatteryPercent() const;

	UFUNCTION(BlueprintCallable, Category = "Player State|Attributes")
	float GetGold() const;

	UFUNCTION(BlueprintCallable, Category = "Player State|Attributes")
	float GetTokens() const;

protected:
	UPROPERTY()
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<class UPlayerAttributeSetBase> AttributeSetBase;

	FGameplayTag DeadTag;

	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;
	FDelegateHandle HealthRegenChangedDelegateHandle;
	FDelegateHandle StaminaChangedDelegateHandle;
	FDelegateHandle MaxStaminaChangedDelegateHandle;
	FDelegateHandle StaminaRegenChangedDelegateHandle;
	FDelegateHandle WalkSpeedChangedDelegateHandle;
	FDelegateHandle DamageReductionChangedDelegateHandle;
	FDelegateHandle CooldownReductionChangedDelegateHandle;
	FDelegateHandle BatteryChargeChangedDelegateHandle;
	FDelegateHandle MaxBatteryChargeChangedDelegateHandle;
	FDelegateHandle BatteryChargeRegenChangedDelegateHandle;
	FDelegateHandle BatteryDrainFlashlightChangedDelegateHandle;
	FDelegateHandle BatteryDrainCommsChangedDelegateHandle;
	FDelegateHandle StealthinessChangedDelegateHandle;
	FDelegateHandle PuzzleTimerChangedDelegateHandle;
	FDelegateHandle FloorEffectResistanceChangedDelegateHandle;
	FDelegateHandle FlashlightSizeChangedDelegateHandle;
	FDelegateHandle MaxReviveCountChangedDelegateHandle;
	FDelegateHandle ReviveChanceChangedDelegateHandle;
	FDelegateHandle ReviveHealthPercentChangedDelegateHandle;
	FDelegateHandle ReviveBatteryPercentChangedDelegateHandle;
	FDelegateHandle GoldChangedDelegateHandle;
	FDelegateHandle TokensChangedDelegateHandle;

	virtual void BeginPlay() override;

	virtual void OnHealthChanged(const FOnAttributeChangeData& Data);
	virtual void OnMaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void OnHealthRegenChanged(const FOnAttributeChangeData& Data);
	virtual void OnStaminaChanged(const FOnAttributeChangeData& Data);
	virtual void OnMaxStaminaChanged(const FOnAttributeChangeData& Data);
	virtual void OnStaminaRegenChanged(const FOnAttributeChangeData& Data);
	virtual void OnWalkSpeedChanged(const FOnAttributeChangeData& Data);
	virtual void OnDamageReductionChanged(const FOnAttributeChangeData& Data);
	virtual void OnCooldownReductionChanged(const FOnAttributeChangeData& Data);
	virtual void OnBatteryChargeChanged(const FOnAttributeChangeData& Data);
	virtual void OnMaxBatteryChargeChanged(const FOnAttributeChangeData& Data);
	virtual void OnBatteryChargeRegenChanged(const FOnAttributeChangeData& Data);
	virtual void OnBatteryDrainFlashlightChanged(const FOnAttributeChangeData& Data);
	virtual void OnBatteryDrainCommsChanged(const FOnAttributeChangeData& Data);
	virtual void OnStealthinessChanged(const FOnAttributeChangeData& Data);
	virtual void OnPuzzleTimerChanged(const FOnAttributeChangeData& Data);
	virtual void OnFloorEffectResistanceChanged(const FOnAttributeChangeData& Data);
	virtual void OnFlashlightSizeChanged(const FOnAttributeChangeData& Data);
	virtual void OnMaxReviveCountChanged(const FOnAttributeChangeData& Data);
	virtual void OnReviveChanceChanged(const FOnAttributeChangeData& Data);
	virtual void OnReviveHealthPercentChanged(const FOnAttributeChangeData& Data);
	virtual void OnReviveBatteryPercentChanged(const FOnAttributeChangeData& Data);
	virtual void OnGoldChanged(const FOnAttributeChangeData& Data);
	virtual void OnTokensChanged(const FOnAttributeChangeData& Data);

	virtual void OnStunTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
};
