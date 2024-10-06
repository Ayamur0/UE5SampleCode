// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DungeonPlayerState.h"
#include "Characters/AttributeSets/PlayerAttributeSetBase.h"
#include "Characters/CharacterAbilitySystemComponent.h"

ADungeonPlayerState::ADungeonPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCharacterAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSetBase = CreateDefaultSubobject<UPlayerAttributeSetBase>(TEXT("AttributeSetBase"));

	NetUpdateFrequency = 100.0f;

	DeadTag = FGameplayTag::RequestGameplayTag(FName(TEXT("State.Dead")));
}

UAbilitySystemComponent* ADungeonPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

TObjectPtr<class UPlayerAttributeSetBase> ADungeonPlayerState::GetAttributeSetBase() const
{
	return AttributeSetBase;
}

bool ADungeonPlayerState::IsAlive() const
{
	return GetHealth() > 0;
}

float ADungeonPlayerState::GetHealth() const
{
	return AttributeSetBase->GetHealth();
}

float ADungeonPlayerState::GetMaxHealth() const
{
	return AttributeSetBase->GetMaxHealth();
}

float ADungeonPlayerState::GetHealthRegen() const
{
	return AttributeSetBase->GetHealthRegen();
}

float ADungeonPlayerState::GetStamina() const
{
	return AttributeSetBase->GetStamina();
}

float ADungeonPlayerState::GetMaxStamina() const
{
	return AttributeSetBase->GetMaxStamina();
}

float ADungeonPlayerState::GetStaminaRegen() const
{
	return AttributeSetBase->GetStaminaRegen();
}

float ADungeonPlayerState::GetWalkSpeed() const
{
	return AttributeSetBase->GetWalkSpeed();
}

float ADungeonPlayerState::GetDamageReduction() const
{
	return AttributeSetBase->GetDamageReduction();
}

float ADungeonPlayerState::GetCooldownReduction() const
{
	return AttributeSetBase->GetCooldownReduction();
}

float ADungeonPlayerState::GetBatteryCharge() const
{
	return AttributeSetBase->GetBatteryCharge();
}

float ADungeonPlayerState::GetMaxBatteryCharge() const
{
	return AttributeSetBase->GetMaxBatteryCharge();
}

float ADungeonPlayerState::GetBatteryChargeRegen() const
{
	return AttributeSetBase->GetBatteryChargeRegen();
}

float ADungeonPlayerState::GetBatteryDrainFlashlight() const
{
	return AttributeSetBase->GetBatteryDrainFlashlight();
}

float ADungeonPlayerState::GetBatteryDrainComms() const
{
	return AttributeSetBase->GetBatteryDrainComms();
}

float ADungeonPlayerState::GetStealthiness() const
{
	return AttributeSetBase->GetStealthiness();
}

float ADungeonPlayerState::GetPuzzleTimer() const
{
	return AttributeSetBase->GetPuzzleTimer();
}

float ADungeonPlayerState::GetFloorEffectResistance() const
{
	return AttributeSetBase->GetFloorEffectResistance();
}

float ADungeonPlayerState::GetFlashlightSize() const
{
	return AttributeSetBase->GetFlashlightSize();
}

float ADungeonPlayerState::GetMaxReviveCount() const
{
	return AttributeSetBase->GetMaxReviveCount();
}

float ADungeonPlayerState::GetReviveChance() const
{
	return AttributeSetBase->GetReviveChance();
}

float ADungeonPlayerState::GetReviveHealthPercent() const
{
	return AttributeSetBase->GetReviveHealthPercent();
}

float ADungeonPlayerState::GetReviveBatteryPercent() const
{
	return AttributeSetBase->GetReviveBatteryPercent();
}

float ADungeonPlayerState::GetGold() const
{
	return AttributeSetBase->GetGold();
}

float ADungeonPlayerState::GetTokens() const
{
	return AttributeSetBase->GetTokens();
}

void ADungeonPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, &ADungeonPlayerState::OnHealthChanged);
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxHealthAttribute()).AddUObject(this, &ADungeonPlayerState::OnMaxHealthChanged);
		HealthRegenChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthRegenAttribute()).AddUObject(this, &ADungeonPlayerState::OnHealthRegenChanged);
		StaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetStaminaAttribute()).AddUObject(this, &ADungeonPlayerState::OnStaminaChanged);
		MaxStaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxStaminaAttribute()).AddUObject(this, &ADungeonPlayerState::OnMaxStaminaChanged);
		StaminaRegenChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetStaminaRegenAttribute()).AddUObject(this, &ADungeonPlayerState::OnStaminaRegenChanged);
		WalkSpeedChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetWalkSpeedAttribute()).AddUObject(this, &ADungeonPlayerState::OnWalkSpeedChanged);
		DamageReductionChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetDamageReductionAttribute()).AddUObject(this, &ADungeonPlayerState::OnDamageReductionChanged);
		CooldownReductionChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetCooldownReductionAttribute()).AddUObject(this, &ADungeonPlayerState::OnCooldownReductionChanged);
		BatteryChargeChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetBatteryChargeAttribute()).AddUObject(this, &ADungeonPlayerState::OnBatteryChargeChanged);
		MaxBatteryChargeChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxBatteryChargeAttribute()).AddUObject(this, &ADungeonPlayerState::OnMaxBatteryChargeChanged);
		BatteryChargeRegenChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetBatteryChargeRegenAttribute()).AddUObject(this, &ADungeonPlayerState::OnBatteryChargeRegenChanged);
		BatteryDrainFlashlightChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetBatteryDrainFlashlightAttribute()).AddUObject(this, &ADungeonPlayerState::OnBatteryDrainFlashlightChanged);
		BatteryDrainCommsChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetBatteryDrainCommsAttribute()).AddUObject(this, &ADungeonPlayerState::OnBatteryDrainCommsChanged);
		StealthinessChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetStealthinessAttribute()).AddUObject(this, &ADungeonPlayerState::OnStealthinessChanged);
		PuzzleTimerChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetPuzzleTimerAttribute()).AddUObject(this, &ADungeonPlayerState::OnPuzzleTimerChanged);
		FloorEffectResistanceChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetFloorEffectResistanceAttribute()).AddUObject(this, &ADungeonPlayerState::OnFloorEffectResistanceChanged);
		FlashlightSizeChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetFlashlightSizeAttribute()).AddUObject(this, &ADungeonPlayerState::OnFlashlightSizeChanged);
		MaxReviveCountChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxReviveCountAttribute()).AddUObject(this, &ADungeonPlayerState::OnMaxReviveCountChanged);
		ReviveChanceChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetReviveChanceAttribute()).AddUObject(this, &ADungeonPlayerState::OnReviveChanceChanged);
		ReviveHealthPercentChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetReviveHealthPercentAttribute()).AddUObject(this, &ADungeonPlayerState::OnReviveHealthPercentChanged);
		ReviveBatteryPercentChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetReviveBatteryPercentAttribute()).AddUObject(this, &ADungeonPlayerState::OnReviveBatteryPercentChanged);
		GoldChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetGoldAttribute()).AddUObject(this, &ADungeonPlayerState::OnGoldChanged);
		TokensChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetTokensAttribute()).AddUObject(this, &ADungeonPlayerState::OnTokensChanged);

		AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName(TEXT("State.Debuff.Stun"))), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ADungeonPlayerState::OnStunTagChanged);
	}
}

void ADungeonPlayerState::OnHealthChanged(const FOnAttributeChangeData& Data)
{
}

void ADungeonPlayerState::OnMaxHealthChanged(const FOnAttributeChangeData& Data)
{
}

void ADungeonPlayerState::OnHealthRegenChanged(const FOnAttributeChangeData& Data)
{
}

void ADungeonPlayerState::OnStaminaChanged(const FOnAttributeChangeData& Data)
{
}

void ADungeonPlayerState::OnMaxStaminaChanged(const FOnAttributeChangeData& Data)
{
}

void ADungeonPlayerState::OnStaminaRegenChanged(const FOnAttributeChangeData& Data)
{
}

void ADungeonPlayerState::OnWalkSpeedChanged(const FOnAttributeChangeData& Data)
{
}

void ADungeonPlayerState::OnDamageReductionChanged(const FOnAttributeChangeData& Data)
{
}

void ADungeonPlayerState::OnCooldownReductionChanged(const FOnAttributeChangeData& Data)
{
}

void ADungeonPlayerState::OnBatteryChargeChanged(const FOnAttributeChangeData& Data)
{
}

void ADungeonPlayerState::OnMaxBatteryChargeChanged(const FOnAttributeChangeData& Data)
{
}

void ADungeonPlayerState::OnBatteryChargeRegenChanged(const FOnAttributeChangeData& Data)
{
}

void ADungeonPlayerState::OnBatteryDrainFlashlightChanged(const FOnAttributeChangeData& Data)
{
}

void ADungeonPlayerState::OnBatteryDrainCommsChanged(const FOnAttributeChangeData& Data)
{
}

void ADungeonPlayerState::OnStealthinessChanged(const FOnAttributeChangeData& Data)
{
}

void ADungeonPlayerState::OnPuzzleTimerChanged(const FOnAttributeChangeData& Data)
{
}

void ADungeonPlayerState::OnFloorEffectResistanceChanged(const FOnAttributeChangeData& Data)
{
}

void ADungeonPlayerState::OnFlashlightSizeChanged(const FOnAttributeChangeData& Data)
{
}

void ADungeonPlayerState::OnMaxReviveCountChanged(const FOnAttributeChangeData& Data)
{
}

void ADungeonPlayerState::OnReviveChanceChanged(const FOnAttributeChangeData& Data)
{
}

void ADungeonPlayerState::OnReviveHealthPercentChanged(const FOnAttributeChangeData& Data)
{
}

void ADungeonPlayerState::OnReviveBatteryPercentChanged(const FOnAttributeChangeData& Data)
{
}

void ADungeonPlayerState::OnGoldChanged(const FOnAttributeChangeData& Data)
{
}

void ADungeonPlayerState::OnTokensChanged(const FOnAttributeChangeData& Data)
{
}


void ADungeonPlayerState::OnStunTagChanged(const FGameplayTag CallbackTag, int32 NewCount) {
	if (NewCount > 0) {
		// Stunned
		FGameplayTagContainer AbilityTagsToCancel;
		AbilityTagsToCancel.AddTag(FGameplayTag::RequestGameplayTag(FName(TEXT("Ability"))));

		FGameplayTagContainer AbilityTagsToIgnore;
		AbilityTagsToIgnore.AddTag(FGameplayTag::RequestGameplayTag(FName(TEXT("Ability.NoCancelByStun"))));

		AbilitySystemComponent->CancelAbilities(&AbilityTagsToCancel, &AbilityTagsToIgnore);
	}
	else {
		// Unstunned
	}
}
