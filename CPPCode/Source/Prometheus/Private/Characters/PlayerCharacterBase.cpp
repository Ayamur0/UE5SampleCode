// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "Characters/CharacterAbilitySystemComponent.h"
#include "Characters/CharacterGameplayAbility.h"
#include "Characters/AttributeSets/PlayerAttributeSetBase.h"
#include "Characters/PromCharacterMovementComponent.h"

// Sets default values
APlayerCharacterBase::APlayerCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UPromCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Overlap);

	bAlwaysRelevant = true;

	DeadTag = FGameplayTag::RequestGameplayTag("State.Dead");
	EffectRemoveOnDeathTag = FGameplayTag::RequestGameplayTag("Effect.RemoveOnDeath");
}

// Called when the game starts or when spawned
void APlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacterBase::AddCharacterAbilities()
{
	// Grant abilities, but only on the server	
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->bCharacterAbilitiesGiven)
	{
		return;
	}

	for (const auto& Entry : CharacterAbilities)
	{
		// Get the InputAction and GameplayAbility from the TMap
		UInputAction* InputAction = Entry.Key;
		TSubclassOf<UCharacterGameplayAbility> StartupAbility = Entry.Value;
		UE_LOG(LogTemp, Warning, TEXT("Giving Abilities to AbilitySystemComponent with default values..."));
		FGameplayAbilitySpecHandle AbilityHandle = AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(StartupAbility, GetAbilityLevel(StartupAbility.GetDefaultObject()->AbilityID), static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
		UE_LOG(LogTemp, Warning, TEXT("Ability Name: %s"), *StartupAbility.GetDefaultObject()->GetName());

		// Add the InputAction and AbilityHandle to the map
		UE_LOG(LogTemp, Warning, TEXT("Adding InputAction %s and AbilityHandle %s to Map"), *InputAction->GetName(), *AbilityHandle.ToString());
		InputToAbilityMap.Add(InputAction, AbilityHandle);
	}

	AbilitySystemComponent->bCharacterAbilitiesGiven = true;
}

void APlayerCharacterBase::InitializeAttributes()
{
	if (!AbilitySystemComponent.IsValid())
	{
		return;
	}

	if (!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	// Can run on Server and Client
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
	}
}

void APlayerCharacterBase::AddStartupEffects()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->bStartupEffectsApplied)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
		}
	}

	AbilitySystemComponent->bStartupEffectsApplied = true;
}

void APlayerCharacterBase::SetHealth(float Health)
{
	if (AttributeSetBase.IsValid())
	{
		AttributeSetBase->SetHealth(Health);
	}
}

void APlayerCharacterBase::SetStamina(float Stamina)
{
	if (AttributeSetBase.IsValid())
	{
		AttributeSetBase->SetStamina(Stamina);
	}
}

void APlayerCharacterBase::SetBatteryCharge(float BatteryCharge)
{
	if (AttributeSetBase.IsValid())
	{
		AttributeSetBase->SetBatteryCharge(BatteryCharge);
	}
}

UAbilitySystemComponent* APlayerCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

bool APlayerCharacterBase::IsAlive() const
{
	return GetHealth() > 0.0f;
}

int32 APlayerCharacterBase::GetAbilityLevel(ECharacterAbilityID AbilityID) const
{
	return 1;
}

void APlayerCharacterBase::RemoveCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || !AbilitySystemComponent->bCharacterAbilitiesGiven)
	{
		return;
	}

	// Remove any abilities added from a previous call. This checks to make sure the ability is in the startup 'CharacterAbilities' array.
	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
	TArray<TSubclassOf<UCharacterGameplayAbility>> AbilityClasses;
	CharacterAbilities.GenerateValueArray(AbilityClasses);
	for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if ((Spec.SourceObject == this) && AbilityClasses.Contains(Spec.Ability->GetClass()))
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}

	// Do in two passes so the removal happens after we have the full list
	for (int32 i = 0; i < AbilitiesToRemove.Num(); i++)
	{
		AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);
	}

	AbilitySystemComponent->bCharacterAbilitiesGiven = false;
}

void APlayerCharacterBase::Die()
{
	// Only runs on Server
	RemoveCharacterAbilities();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->Velocity = FVector(0);

	OnCharacterDied.Broadcast(this);

	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->CancelAllAbilities();

		FGameplayTagContainer EffectTagsToRemove;
		EffectTagsToRemove.AddTag(EffectRemoveOnDeathTag);
		int32 NumEffectsRemoved = AbilitySystemComponent->RemoveActiveEffectsWithTags(EffectTagsToRemove);

		AbilitySystemComponent->AddLooseGameplayTag(DeadTag);
	}

	if (DeathMontage)
	{
		PlayAnimMontage(DeathMontage);
	}
	else
	{
		FinishDying();
	}
}

void APlayerCharacterBase::FinishDying()
{
	Destroy();
}

float APlayerCharacterBase::GetHealth() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetHealth();
	}

	return 0.0f;
}

float APlayerCharacterBase::GetMaxHealth() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMaxHealth();
	}

	return 0.0f;
}

float APlayerCharacterBase::GetHealthRegen() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetHealthRegen();
	}

	return 0.0f;
}

float APlayerCharacterBase::GetStamina() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetStamina();
	}

	return 0.0f;
}

float APlayerCharacterBase::GetMaxStamina() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMaxStamina();
	}

	return 0.0f;
}

float APlayerCharacterBase::GetStaminaRegen() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetStaminaRegen();
	}

	return 0.0f;
}

float APlayerCharacterBase::GetWalkSpeed() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetWalkSpeed();
	}

	return 0.0f;
}

float APlayerCharacterBase::GetDamageReduction() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetDamageReduction();
	}

	return 0.0f;

}

float APlayerCharacterBase::GetCooldownReduction() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetCooldownReduction();
	}

	return 0.0f;
}

float APlayerCharacterBase::GetBatteryCharge() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetBatteryCharge();
	}

	return 0.0f;
}

float APlayerCharacterBase::GetMaxBatteryCharge() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMaxBatteryCharge();
	}

	return 0.0f;
}

float APlayerCharacterBase::GetBatteryChargeRegen() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetBatteryChargeRegen();
	}

	return 0.0f;

}

float APlayerCharacterBase::GetBatteryDrainFlashlight() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetBatteryDrainFlashlight();
	}

	return 0.0f;
}

float APlayerCharacterBase::GetBatteryDrainComms() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetBatteryDrainComms();
	}

	return 0.0f;
}

float APlayerCharacterBase::GetStealthiness() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetStealthiness();
	}

	return 0.0f;
}

float APlayerCharacterBase::GetPuzzleTimer() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetPuzzleTimer();
	}

	return 0.0f;
}

float APlayerCharacterBase::GetFloorEffectResistance() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetFloorEffectResistance();
	}

	return 0.0f;

}

float APlayerCharacterBase::GetFlashlightSize() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetFlashlightSize();
	}

	return 0.0f;
}

float APlayerCharacterBase::GetMaxReviveCount() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMaxReviveCount();
	}

	return 0.0f;
}

float APlayerCharacterBase::GetReviveChance() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetReviveChance();
	}

	return 0.0f;
}

float APlayerCharacterBase::GetReviveHealthPercent() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetReviveHealthPercent();
	}

	return 0.0f;
}

float APlayerCharacterBase::GetReviveBatteryPercent() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetReviveBatteryPercent();
	}

	return 0.0f;
}

float APlayerCharacterBase::GetGold() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetGold();
	}

	return 0.0f;
}

float APlayerCharacterBase::GetTokens() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetTokens();
	}

	return 0.0f;
}

