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
	if (bInputPressed)
	{
		if (!bIsWaitingToRun && !bIsRunning && HasEnoughStaminaToStartRunning())
		{
			bIsWaitingToRun = true;
		}
	}
	else
	{
		bIsWaitingToRun = false;
		bIsRunning = false;
	}

	HandleDelay();
    HandleStamina();
	HandleAcceleration();
}

float URealisticRunningComponent::GetMaxRunSpeed()
{
	return  MaxRunSpeed;
}

float URealisticRunningComponent::GetMaxWalkSpeed()
{
	return MaxWalkSpeed;
}

void URealisticRunningComponent::HandleDelay()
{
	if (bIsWaitingToRun)
	{
		StartRunningDelayTimer += FixedTime;

		if (HasEnoughStaminaToStartRunning())
		{
			if (StartRunningDelayTimer >= StartRunningDelay)
			{
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
			}
		}
	}
	else
	{
		if (MaxSpeedTransitionTimer > 0)
		{
			MaxSpeedTransitionTimer -= FixedTime * BrakingRatio;

			CharacterMovement->MaxWalkSpeed = FMath::Lerp(MaxWalkSpeed, MaxRunSpeed, MaxSpeedTransitionTimer / MaxSpeedTransitionTime);;
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
			bIsRunning = false;
			StartRunningDelayTimer = 0;
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

bool URealisticRunningComponent::ReachedRunningSpeed()
{
	return FMath::IsNearlyEqual(CharacterMovement->MaxWalkSpeed, MaxRunSpeed, 50) ; 
}

void URealisticRunningComponent::RunBeginAction()
{
	bInputPressed = true;
}

void URealisticRunningComponent::RunEndAction()
{
	bInputPressed = false;
}

void URealisticRunningComponent::Initialize()
{
	CharacterMovement = GetOwner()->GetComponentByClass<UCharacterMovementComponent>();

	CharacterMovement->MaxWalkSpeed = MaxWalkSpeed;
}

