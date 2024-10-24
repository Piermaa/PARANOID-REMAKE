// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraShakeSelectorComponent.h"

#include "RealisticRunningComponent.h"
#include "Chaos/KinematicTargets.h"
#include "GameFramework/CharacterMovementComponent.h"

UCameraShakeSelectorComponent::UCameraShakeSelectorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCameraShakeSelectorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCameraShakeSelectorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCameraShakeSelectorComponent::SelectCameraShake() const
{
	if(PlayerController!=nullptr && RealisticRunningComponent != nullptr)
	{
		if(HasOverride)
		{
			if(OverrideCameraShake != nullptr)
			{
				PlayerController->ClientStartCameraShake(
				OverrideCameraShake,
				1,
				ECameraShakePlaySpace::CameraLocal,
				FRotator(0,0,0)
				);
			}
			return;
		}
	

		
		float Velocity = CharacterMovementComponent->Velocity.Length();
		float CurrentMaxVelocity=0;
		float CameraShakeIntensity=1;
		TSubclassOf<UCameraShakeBase> CurrentCameraShake=IdleCameraShake;

		if(Velocity > 0)
		{
			if(Velocity <= RealisticRunningComponent->GetMaxWalkSpeed())
			{
				CurrentCameraShake = WalkCameraShake;
				CurrentMaxVelocity=RealisticRunningComponent->GetMaxWalkSpeed();
			}
			else
			{
				CurrentCameraShake = RunCameraShake;
				CurrentMaxVelocity=RealisticRunningComponent->GetMaxRunSpeed();
			}
		}
	
		if(CurrentMaxVelocity != 0)
		{
			CameraShakeIntensity = 0.5f + Velocity/CurrentMaxVelocity;
			CameraShakeIntensity = CameraShakeIntensity > 1 ? 1: CameraShakeIntensity; 
		}

		if(CurrentCameraShake != nullptr)
		{
			PlayerController->ClientStartCameraShake(
				CurrentCameraShake,
				CameraShakeIntensity,
				ECameraShakePlaySpace::CameraLocal,
				FRotator(0,0,0)
			);
		}
	}
	
}

void UCameraShakeSelectorComponent::Initialize(
	UCharacterMovementComponent* NewCharacterMovementComponent,
	AController* Controller,
	URealisticRunningComponent* NewRealisticRunningComponent)
{
	CharacterMovementComponent = NewCharacterMovementComponent;
	PlayerController = Cast<APlayerController>(Controller);
	RealisticRunningComponent = NewRealisticRunningComponent;
}

void UCameraShakeSelectorComponent::SetOverrideCameraShake(TSubclassOf<UCameraShakeBase> NewCameraShake)
{
	OverrideCameraShake = NewCameraShake;
	HasOverride = true;
}

void UCameraShakeSelectorComponent::ClearCameraShakeOverride()
{
	HasOverride = false;
}

