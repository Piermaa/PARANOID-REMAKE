// Fill out your copyright notice in the Description page of Project Settings.


#include "RealisticRunningComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
URealisticRunningComponent::URealisticRunningComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void URealisticRunningComponent::BeginPlay()
{
	Super::BeginPlay();
	RemainingStaminaInSeconds = MaxStaminaInSeconds;
}


void URealisticRunningComponent::HandleMovementSpeed()
{
	HandleDelay();
    HandleStamina();
	HandleAcceleration();
}

void URealisticRunningComponent::HandleDelay()
{
	if (bIsWaitingToRun)
	{
		StartRunningDelayTimer += FixedTime;
		UE_LOG(LogTemp, Warning, TEXT("StartRunningDelayTimer: %f"), StartRunningDelayTimer);

		if (HasEnoughStaminaToStartRunning())
		{
			if (StartRunningDelayTimer >= StartRunningDelay)
			{
				UE_LOG(LogTemp, Warning, TEXT("Run Started"));

				bIsRunning = true;
				bIsWaitingToRun = false;
				StartRunningDelayTimer = 0;
			}
		}
	}
}

void URealisticRunningComponent::HandleAcceleration()
{
	if (bIsRunning)
	{
		if (CharacterMovement->MaxWalkSpeed < MaxRunSpeed)
		{
			if (MaxSpeedTransitionTimer < MaxSpeedTransitionTime)
			{
				MaxSpeedTransitionTimer += FixedTime;

				CharacterMovement->MaxWalkSpeed = FMath::Lerp(MaxWalkSpeed, MaxRunSpeed, MaxSpeedTransitionTimer / MaxSpeedTransitionTime);;
				UE_LOG(LogTemp, Display, TEXT("Runspeed: %f"), CharacterMovement->MaxWalkSpeed);
			}
		}
	}
	else
	{
		if (MaxSpeedTransitionTimer > 0)
		{
			MaxSpeedTransitionTimer -= FixedTime * BrakingRatio;

			CharacterMovement->MaxWalkSpeed = FMath::Lerp(MaxWalkSpeed, MaxRunSpeed, MaxSpeedTransitionTimer / MaxSpeedTransitionTime);;
			UE_LOG(LogTemp, Warning, TEXT("Runspeed: %f"), CharacterMovement->MaxWalkSpeed);
		}
	}
}

void URealisticRunningComponent::HandleStamina()
{
	if (bIsRunning)
	{
		if (RemainingStaminaInSeconds>0)
		{
			RemainingStaminaInSeconds -= FixedTime;
		}
		

		if (!HasEnoughStaminaToRun())
		{
			RunEndAction();
			RemainingStaminaInSeconds = 0;
		}
	}
	else
	{
		if (RemainingStaminaInSeconds < MaxStaminaInSeconds)
		{
			RemainingStaminaInSeconds += FixedTime * StaminaRecoveryRatio;
		}
		else
		{
			RemainingStaminaInSeconds = MaxStaminaInSeconds;
		}
	}
}

bool URealisticRunningComponent::HasEnoughStaminaToRun()
{
	return RemainingStaminaInSeconds/MaxStaminaInSeconds > 0;
}

bool URealisticRunningComponent::HasEnoughStaminaToStartRunning()
{
	return RemainingStaminaInSeconds / MaxStaminaInSeconds >= MinimalRemainingStaminaPercentageToStartRunning;
}

void URealisticRunningComponent::RunBeginAction()
{
	UE_LOG(LogTemp, Warning, TEXT("Run Begin"));

	if (!bIsWaitingToRun && !bIsRunning)
	{
		bIsWaitingToRun=true;
	}
}

void URealisticRunningComponent::RunEndAction()
{
	UE_LOG(LogTemp, Warning, TEXT("RunEnd"));
	bIsRunning = false;
	StartRunningDelayTimer = 0;
}

void URealisticRunningComponent::Initialize()
{
	CharacterMovement = GetOwner()->GetComponentByClass<UCharacterMovementComponent>();

	CharacterMovement->MaxWalkSpeed = MaxWalkSpeed;
}

