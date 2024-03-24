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
		//CurrentCameraShake->;

		//UE_LOG(LogTemp, Display, TEXT("CameraShakeName: %s"), &CsName);
	
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

void UCameraShakeSelectorComponent::SetCharacterMovementComponent(
	UCharacterMovementComponent* NewCharacterMovementComponent,
	AController* Controller,
	URealisticRunningComponent* NewRealisticRunningComponent)
{
	CharacterMovementComponent = NewCharacterMovementComponent;
	PlayerController = Cast<APlayerController>(Controller);
	RealisticRunningComponent = NewRealisticRunningComponent;
}

