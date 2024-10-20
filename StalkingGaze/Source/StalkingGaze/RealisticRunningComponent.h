// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <EnhancedInputLibrary.h>
#include "InputAction.h"
#include "InputActionValue.h"
#include "RealisticRunningComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STALKINGGAZE_API URealisticRunningComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URealisticRunningComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:
	void RunBeginAction();
	void RunEndAction();
	void Initialize();
	void HandleMovementSpeed();
	float GetMaxRunSpeed();
	float GetMaxWalkSpeed();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool ReachedRunningSpeed();
	
private:
	class UCharacterMovementComponent* CharacterMovement;

	UPROPERTY(EditDefaultsOnly, Category = "Movement Values | Speed", meta = (AllowPrivateAccess = "true"))
	float MaxRunSpeed = 600.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement Values | Speed", meta = (AllowPrivateAccess = "true"))
	float MaxWalkSpeed = 275.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement Values | Speed", meta = (AllowPrivateAccess = "true"))
	float BrakingRatio = 2;

	UPROPERTY(EditDefaultsOnly, Category = "Movement Values | Timers", meta = (AllowPrivateAccess = "true"))
	float MaxSpeedTransitionTime = 0.5;

	UPROPERTY(EditDefaultsOnly, Category = "Movement Values | Timers", meta = (AllowPrivateAccess = "true"))
	float StartRunningDelay = 0.5;

	UPROPERTY(EditDefaultsOnly, Category = "Movement Values | Stamina", meta = (AllowPrivateAccess = "true"))
	float MaxStaminaInSeconds = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Movement Values | Stamina", meta = (AllowPrivateAccess = "true"))
	float MinimalRemainingStaminaPercentageToStartRunning = 0.95f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement Values | Stamina", meta = (AllowPrivateAccess = "true"))
	float StaminaRecoveryRatio = 2;

	float MaxSpeedTransitionTimer = 0;
	float StartRunningDelayTimer = 0;
	float RemainingStaminaInSeconds = 0;
	bool bIsRunning = false;
	bool bIsWaitingToRun = false;
	bool bInputPressed;

	float FixedTime = 0.02f;

	//###############
	//###Functions###
	//###############

	void HandleDelay();
	void HandleAcceleration();
	void HandleStamina();
	bool HasEnoughStaminaToRun();
	bool HasEnoughStaminaToStartRunning();
};
