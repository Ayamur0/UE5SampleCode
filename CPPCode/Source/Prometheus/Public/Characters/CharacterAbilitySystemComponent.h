// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "EnhancedInputComponent.h"
#include "CharacterAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReceivedDamageDelegate, UCharacterAbilitySystemComponent*, SourceASC, float, UnmitigatedDamage, float, MitigatedDamage);

USTRUCT()
struct FAbilityInputBinding
{
	GENERATED_BODY()

	int32 InputID;
	uint32 OnPressedHandle = 0;
	uint32 OnReleasedHandle = 0;
	TArray<FGameplayAbilitySpecHandle> BoundAbilitiesStack;
};

UCLASS(Blueprintable, BlueprintType, Category = "AbilityInput", meta=(BlueprintSpawnableComponent))
class PROMETHEUS_API UCharacterAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Enhanced Input Abilities")
	void SetInputBinding(UInputAction* InputAction, const FGameplayAbilitySpecHandle& AbilityHandle);

	UFUNCTION(BlueprintCallable, Category = "Enhanced Input Abilities")
	void ClearInputBinding(const FGameplayAbilitySpecHandle& AbilityHandle);

	UFUNCTION(BlueprintCallable, Category = "Enhanced Input Abilities")
	void ClearAbilityBindings(const UInputAction* InputAction);

	bool bCharacterAbilitiesGiven{ false };
	bool bStartupEffectsApplied{ false };

	FReceivedDamageDelegate ReceivedDamage;

public:
	virtual void ReceiveDamage(UCharacterAbilitySystemComponent* SourceASC, float UnmitigatedDamage, float MitigatedDamage);

private:
	bool bInputComponentInitialized{ false };

	void InitializeInputComponent();

	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;

	void OnAbilityInputPressed(const UInputAction* InputAction);

	void OnAbilityInputReleased(const UInputAction* InputAction);

	void RemoveEntry(const UInputAction* InputAction);

	void TryBindAbilityInput(const UInputAction* InputAction, FAbilityInputBinding& AbilityInputBinding);

	virtual void BeginPlay() override;

	UPROPERTY(transient)
	TMap<UInputAction*, FAbilityInputBinding> MappedAbilities;

	UPROPERTY(transient)
	UEnhancedInputComponent* InputComponent;
};
