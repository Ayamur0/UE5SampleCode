// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Characters/CharacterAbilityID.h"
#include "GameplayTagContainer.h"
#include "EnhancedInputSubSystems.h"
#include "AbilitySystemComponent.h"
#include "PlayerCharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate, APlayerCharacterBase*, Character);

UCLASS()
class PROMETHEUS_API APlayerCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacterBase(const class FObjectInitializer& ObjectInitializer);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UPROPERTY(BlueprintAssignable, Category = "Player|Character")
	FCharacterDiedDelegate OnCharacterDied;

	UFUNCTION(BlueprintCallable, Category = "Player|Character")
	virtual bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Character")
	virtual int32 GetAbilityLevel(ECharacterAbilityID AbilityID) const;

	//Only called by server, removes on client too
	virtual void RemoveCharacterAbilities();

	virtual void Die();

	UFUNCTION(BlueprintCallable, Category = "Player|Character")
	virtual void FinishDying();

	UFUNCTION(BlueprintCallable, Category = "Player|Character|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Character|Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Character|Attributes")
	float GetHealthRegen() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Character|Attributes")
	float GetStamina() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Character|Attributes")
	float GetMaxStamina() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Character|Attributes")
	float GetStaminaRegen() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Character|Attributes")
	float GetWalkSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Character|Attributes")
	float GetDamageReduction() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Character|Attributes")
	float GetCooldownReduction() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Character|Attributes")
	float GetBatteryCharge() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Character|Attributes")
	float GetMaxBatteryCharge() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Character|Attributes")
	float GetBatteryChargeRegen() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Character|Attributes")
	float GetBatteryDrainFlashlight() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Character|Attributes")
	float GetBatteryDrainComms() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Character|Attributes")
	float GetStealthiness() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Character|Attributes")
	float GetPuzzleTimer() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Character|Attributes")
	float GetFloorEffectResistance() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Character|Attributes")
	float GetFlashlightSize() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Character|Attributes")
	float GetMaxReviveCount() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Character|Attributes")
	float GetReviveChance() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Character|Attributes")
	float GetReviveHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Character|Attributes")
	float GetReviveBatteryPercent() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Character|Attributes")
	float GetGold() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Character|Attributes")
	float GetTokens() const;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TWeakObjectPtr<class UCharacterAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<class UPlayerAttributeSetBase> AttributeSetBase;

	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Player|Character")
	FText CharacterName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player|Animation")
	UAnimMontage* DeathMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Player|Abilities")
	TMap<UInputAction*, TSubclassOf<class UCharacterGameplayAbility>> CharacterAbilities;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player|Abilities")
	TMap<UInputAction*, FGameplayAbilitySpecHandle> InputToAbilityMap;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Player|Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Player|Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	virtual void AddCharacterAbilities();

	virtual void InitializeAttributes();

	virtual void AddStartupEffects();

	virtual void SetHealth(float Health);

	virtual void SetStamina(float Stamina);

	virtual void SetBatteryCharge(float BatteryCharge);
	
};
