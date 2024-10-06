// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/PlayerCharacterBase.h"
#include "DungeonPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROMETHEUS_API ADungeonPlayerCharacter : public APlayerCharacterBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* ThirdPersonCamera;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/**Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction * MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	UPROPERTY(BlueprintReadWrite, Category = Movement)
	bool bBlockMoveInput = false;

	UFUNCTION(BlueprintImplementableEvent, Category = "Player|Character", meta = (DisplayName = "On Player State Changed"))
	void BP_OnRep_PlayerState();

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void ToggleCamera();

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SetActiveCamera(const bool UseFPCamera);

	ADungeonPlayerCharacter(const class FObjectInitializer& ObjectInitializer);

	virtual void PossessedBy(AController* NewController) override;

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE class UCameraComponent* GetThirdPersonCamera() const { return ThirdPersonCamera; }

	FORCEINLINE class UCameraComponent* GetFirstPersonCamera() const { return FirstPersonCamera; }

protected:
	bool bASCInputBound = false;

	bool bIsFirstPerson = false;

	FGameplayTag DeadTag;

	virtual void BeginPlay() override;

	virtual void OnRep_PlayerState() override;

	void BindASCInput();

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
